#include "B1ActionInitialization.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1SteppingAction.hh"
#include "B1TrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


B1ActionInitialization::B1ActionInitialization(DataManager* root, B1Config* conf, B1DetectorConstruction* det)
 : G4VUserActionInitialization()
{
  data_manager = root;
  config = conf;
  detector_construction = det;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1ActionInitialization::~B1ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1ActionInitialization::BuildForMaster() const
{
  SetUserAction(new B1RunAction(data_manager));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1ActionInitialization::Build() const
{
  SetUserAction(new B1PrimaryGeneratorAction(config));
  SetUserAction(new B1RunAction(data_manager));

  B1EventAction* eventAction = new B1EventAction(data_manager);
  SetUserAction(eventAction);

  SetUserAction(new B1SteppingAction(eventAction,data_manager,detector_construction,config->Get_kB()));
  SetUserAction(new B1TrackingAction(data_manager,detector_construction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
