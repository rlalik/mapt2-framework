#include "UserGeant4Geometry.h"


UserGeant4Geometry::UserGeant4Geometry(string filePath, bool drawable_)
{
    drawable = drawable_;
    geometryFilePath = filePath;
    reader = new GeometryReadIn (this, filePath);
    nav = NULL;

    safety = 0.000000001;
}

void UserGeant4Geometry::construct ()
{
    std::cout << "Start geometry construction" << "\n";
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    //vacuum for world
    G4Material* vacuum =
           new G4Material("Vacuum",         //Name as String
                          1,	            //Atomic Number,  in this case we use 1 for hydrogen
                          1.008*g/mole,     //Mass per Mole "Atomic Weight"  1.008*g/mole for Hydorgen
                          1.e-25*g/cm3,     //Density of Vaccuum  *Cant be Zero, Must be small insted
                          kStateGas,        //kStateGas for Gas
                          2.73*kelvin,      //Temperature for ga
                          1.e-25*g/cm3);    //Pressure for Vaccum


    //
    // World
    //
    G4double world_sizeXY =120*cm;
    G4double world_sizeZ  =120*cm;

    G4Box* solidWorld =
      new G4Box("World",0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);

    G4LogicalVolume* logicWorld =
      new G4LogicalVolume(solidWorld,          //its solid
                          vacuum,              //its material
                          "World");            //its name

    world =
      new G4PVPlacement(0,                     //no rotation
                        G4ThreeVector(),       //at (0,0,0)
                        logicWorld,            //its logical volume
                        "World",               //its name
                        0,                     //its mother  volume
                        false,                 //no boolean operation
                        0,                     //copy number
                        true);                 //overlaps checking


    // Read in the geometry text file. The geometry reader adds all parts to the part list.
    reader->read();

    // Placement of the parts in the part list
    // The placement information is already included in CAD, so no rotation or transition of the parts is needed.
    G4VPhysicalVolume* cad_physical;
    G4RotationMatrix * rot = new G4RotationMatrix();
    rot->rotateZ(0*deg);
    if(parts.size() > 0)
    {
        for (int i = 0; i<parts.size();i++)
        {
            cad_physical = new G4PVPlacement(rot, G4ThreeVector(), parts.at(i)->getLogical(), "cad",logicWorld, false, 0);
        }
    }

    nav = new G4Navigator ();
    nav->SetWorldVolume(world);

    std::cout << "Finished geometry construction" << "\n";
}




void UserGeant4Geometry::addPart (AbsPart* part_)
{
    if (part_ != NULL)
    {
        // set the part's volumeIndex as the size of the part list
        part_->setVolumeIndex(parts.size());
        parts.push_back(part_);
    }
}

CADFiber* UserGeant4Geometry::getFiber(int x, int y)
{
    CADFiber* fiber;
    for (int i=0;i<parts.size();i++)
    {
        fiber = dynamic_cast<CADFiber*> (parts.at(i));
        if (fiber != 0)
        {
            if ((fiber->getFiberX() == x) && (fiber->getFiberY() == y))
            {
                return fiber;
            }
        }
    }
    return NULL;
}

AbsPart* UserGeant4Geometry::getPart (G4LogicalVolume* vol)
{
    for (int i=0;i<parts.size();i++)
    {
        if (parts[i]->getLogical() == vol)
        {
            return parts[i];
        }
    }
    return NULL;
}

AbsPart* UserGeant4Geometry::getPart (int volumeIndex_)
{
    for (int i=0;i<parts.size();i++)
    {
        if (parts[i]->getVolumeIndex() == volumeIndex_)
        {
            return parts[i];
        }
    }
    return NULL;
}



AbsPart* UserGeant4Geometry::getCurrentPart (int volumeIndex_) {
    return parts[volumeIndex_];
}


G4LogicalVolume* UserGeant4Geometry::getCurrentPart (TVector3 pos) {
    return nav->LocateGlobalPointAndSetup(G4ThreeVector(pos.X(),pos.Y(),pos.Z()))->GetLogicalVolume();
}


int UserGeant4Geometry::getNextStep (TVector3 pIn, TVector3 dir, TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex_) {
    // shift pIn in dir for safety
    pIn = pIn + dir * safety;
    // get current logical volume
    G4LogicalVolume* currentLogical = getCurrentPart(pIn);

    // check if volume is world
    if (currentLogical->GetName() == "World") {
        // find next intersection point
        TVector3 intersection (0,0,0);
        if (!findNextIntersectionPoint(pIn,dir,intersection)) {
            // kInfinity -> left world
            return 0; // left world => 0
        }
        // intersection is newPIn
        newPIn = intersection;
        // find second intersection point
        intersection = TVector3 (0,0,0);
        if (!findNextIntersectionPoint(newPIn,dir,intersection)) {
            // kInfinity -> Error, because newPIn should be the entry point to a volume
            std::cerr << "[Error] UserGeant4Geometry->getNextStep() :: kInfinity, but pIn should be in a volume" << "\n";
            return -1; // error => -1
        }
        // intersection is newPOut
        newPOut = intersection;
    }
    else { // volume is not world
        // newPIn is pIn
        newPIn = pIn;
        // find second intersection point
        TVector3 intersection (0,0,0);
        if (!findNextIntersectionPoint(newPIn,dir,intersection)) {
            // kInfinity -> Error, because newPIn should be the entry point to a volume
            std::cerr << "[Error] UserGeant4Geometry->getNextStep() :: kInfinity, but pIn should be in a volume" << "\n";
            return -1; // error => -1
        }
        // intersection is newPOut
        newPOut = intersection;
    }
    // get the volumeIndex
    AbsPart* p = getPart(getCurrentPart(newPOut));
    if (p != NULL) {
        volumeIndex_ = p->getVolumeIndex();
        return 1;
    }
    else {
        std::cerr << "[Error] UserGeant4Geometry->getNextStep() :: getPart(newPIn) == NULL" << "\n";
        return -1;
    }
}

bool UserGeant4Geometry::findNextIntersectionPoint (TVector3 startPoint, TVector3 direction, TVector3 &intersection) {
    // get current logical volume
    direction.SetMag(1);
    G4LogicalVolume* currentLogical = getCurrentPart(startPoint);
    G4double prop = 100.0;
    G4double safe = 100.0;
    G4ThreeVector start = G4ThreeVector(startPoint.X(),startPoint.Y(),startPoint.Z());
    G4ThreeVector dir = G4ThreeVector(direction.X(),direction.Y(),direction.Z());
    G4double stepSize= nav->ComputeStep(start,dir,prop,safe);
    if (stepSize == kInfinity)
        return false;
    intersection =  startPoint + stepSize * direction;
    return true;
}



void UserGeant4Geometry::setMaxStepInFiber (double maxStep)
{
    for (int i=0; i<parts.size();i++) {
        CADFiber* fiber;
        if (fiber = dynamic_cast <CADFiber*> (parts[i])) {
            fiber->setMaxStep(maxStep * nm);
        }
    }
}
