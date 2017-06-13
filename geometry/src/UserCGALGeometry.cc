#include "UserCGALGeometry.h"


UserCGALGeometry::UserCGALGeometry(string filePath, bool drawable_)
{
    // drawable is false until now. CGAL geometry is not split up to triangles in the geometry lib
    drawable = false;
    mesh = new TTriangleMesh();
    reader = new GeometryReadInCGAL (this, filePath);
}

void UserCGALGeometry::construct ()
{
    std::cout << "Start geometry construction" << "\n";
    // Read in
    reader->read();

    // initialize whole geometry
    mesh->Init();
    std::cout << "Finished geometry construction" << "\n";
}



void UserCGALGeometry::addPart (AbsPartCGAL* part_)
{
    if (part_ != NULL) {
        int index = parts.size();
        part_->setVolumeIndex(index);
        // load CAD file and insert triangles to mesh
        // cast AbsPart to CADPart
        CADPartCGAL* p = static_cast<CADPartCGAL*> (part_);
        if (p == NULL) {
            std::cout << "Error in addPart: cast problem -> no CADPart" << "\n";
            return;
        }
        mesh->ReadFile(p->getPath().c_str(),index);
        parts.push_back(part_);
    }
}


int UserCGALGeometry::getNextStep (TVector3 startPoint, TVector3 direction, TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex)
{
    return mesh->nextIntersection2 (startPoint,direction,newPIn,newPOut,volumeIndex);
}


CADFiberCGAL* UserCGALGeometry::getFiber(int x, int y)
{
    CADFiberCGAL* fiber;
    for (int i=0;i<parts.size();i++)
    {
        fiber = dynamic_cast<CADFiberCGAL*> (parts.at(i));
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


AbsPartCGAL* UserCGALGeometry::getCurrentPart (int volumeIndex_) {
    return parts[volumeIndex_];
}
