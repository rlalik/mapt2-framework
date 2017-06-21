
#include "B1PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4NeutronTrackingCut.hh"

#include "G4DataQuestionaire.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4OpticalProcessIndex.hh"
#include "G4OpticalPhysics.hh"
#include "G4Scintillation.hh"

#include "MAPTEMStandardPhysics.hh"

B1PhysicsList::B1PhysicsList (B1Config* conf) : G4VModularPhysicsList()
{
    config = conf;
    G4DataQuestionaire it(photon);
    G4int ver =1;
    SetVerboseLevel(ver);

    // EM Physics
//     RegisterPhysics( new MAPTEmStandardPhysics(ver));

    // // EM Physics
    // RegisterPhysics( new G4EmStandardPhysics(ver));
    //
    // // Synchroton Radiation & GN Physics
    // RegisterPhysics( new G4EmExtraPhysics(ver) );
    //
    // // Decays
    // RegisterPhysics( new G4DecayPhysics(ver) );
    //
    // // Hadron Elastic scattering
    // RegisterPhysics( new G4HadronElasticPhysics(ver) );
    //
    // // Hadron Physics
    RegisterPhysics(  new G4HadronPhysicsFTFP_BERT(ver));
    //
    // // Stopping Physics
    // RegisterPhysics( new G4StoppingPhysics(ver) );
    //
    // // Ion Physics
    // RegisterPhysics( new G4IonPhysics(ver));
    //
    // // Neutron tracking cut
    // RegisterPhysics( new G4NeutronTrackingCut(ver));

    // Are optical processes switched on? -> yes -> Register opticalPhysics
    if (config->Get_optical_processes())
    {
        // optical processes and optical physics
        G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();

        opticalPhysics->SetScintillationYieldFactor(1.0);
        opticalPhysics->SetScintillationExcitationRatio(0.0);

        opticalPhysics->SetTrackSecondariesFirst(kCerenkov,true);
        opticalPhysics->SetTrackSecondariesFirst(kScintillation,true);

        RegisterPhysics(opticalPhysics);
    }
}

B1PhysicsList::~B1PhysicsList ()
{

}

void B1PhysicsList::SetCuts ()
{
  G4VUserPhysicsList::SetCuts();

  SetCutValue(config->Get_electronCutValue(), "e-");
}
