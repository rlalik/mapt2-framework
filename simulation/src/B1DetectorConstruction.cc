#include "B1DetectorConstruction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction(B1Config* conf)
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{
  config = conf;
  geometry_filename = config->Get_geometry_file ();
  geo = new UserGeant4Geometry(geometry_filename);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
  geo->construct();
  geo->setMaxStepInFiber(config->Get_maxStep());
  return geo->getWorld();
}
