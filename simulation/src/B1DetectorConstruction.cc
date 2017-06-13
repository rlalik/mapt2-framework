#include "B1DetectorConstruction.hh"

B1DetectorConstruction::B1DetectorConstruction(B1Config* conf)
: G4VUserDetectorConstruction(),
fScoringVolume(0)
{
    config = conf;
    geometry_filename = config->Get_geometry_file ();
    geo = new UserGeant4Geometry(geometry_filename);
}

B1DetectorConstruction::~B1DetectorConstruction()
{
}

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
    geo->construct();
    geo->setMaxStepInFiber(config->Get_maxStep());
    return geo->getWorld();
}
