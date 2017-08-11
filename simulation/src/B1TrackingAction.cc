#include "G4DynamicParticle.hh"
#include "G4VProcess.hh"
#include "G4OpticalPhoton.hh"

#include "B1TrackingAction.hh"
#include "B1EventAction.hh"

#include <MDataManager.h>
#include <MGeantTrack.h>
#include <MGeantFibersRaw.h>

B1TrackingAction::B1TrackingAction(B1EventAction* eventAction, MDataManager* root, B1DetectorConstruction* det) :
    G4UserTrackingAction(), fEventAction(eventAction)
{
    data_manager = root;
    detector_construction  = det;
}

void B1TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    // Get ID of current track
    int track_ID = track->GetTrackID();

    current_particle = fEventAction->addTrack(track_ID);

    current_particle->setTrackID(track_ID);

    if( track_ID  == 1)  // primary
    {
        // set particle creation process
        current_particle->setGenerationProcess("ParticleGun");
    }
    else
    {
        // set particle creation process
        const G4String creator_process_name = track->GetCreatorProcess()->GetProcessName();
        current_particle->setGenerationProcess(creator_process_name);
    }

    current_particle->setParentID(track->GetParentID());

    // Optical Photons
    // decide if particle is an optic photon
    // if yes, then find the logical volume, count the photon in detector_response and kill this photon track
    if(track->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition())
    {
        G4LogicalVolume* volume = track->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        // get the DetectorPart according to the current step logical volume
        AbsPart* part = detector_construction->getGeo()->getPart(volume);
        
        // does the part exist?
        if (part == NULL)
        {
            return;
        }
        
        // Photon in fiber
        // is the current volume a fiber?
        CADFiber* fiber = dynamic_cast<CADFiber*> (part);
        if (fiber)
        {
            MCategory * catGeantFibersRaw = data_manager->getCategory(MCategory::CatGeantFibersRaw);
            int x_fiber = fiber->getFiberX();
            int y_fiber = fiber->getFiberY();
            MLocator loc(3);
            loc[0] = 0;
            loc[1] = y_fiber;
            loc[2] = x_fiber;

            MGeantFibersRaw * detector_response = (MGeantFibersRaw *) catGeantFibersRaw->getObject(loc);
            if (!detector_response)
            {
                detector_response = (MGeantFibersRaw *) catGeantFibersRaw->getSlot(loc);
                detector_response = new (detector_response) MGeantFibersRaw;
                detector_response->setX(x_fiber);
                detector_response->setY(y_fiber);
            }

            detector_response->setPhotons(1);
        }
        
        ((G4Track*)track)->SetTrackStatus(fStopAndKill);
    }

    // Fill the current particle with information
    // start position
    G4ThreeVector start_position = track->GetPosition();
    current_particle->setStartXYZ(start_position.x(),start_position.y(),start_position.z());
    
    // start direction
    G4ThreeVector start_direction = track->GetMomentumDirection();
    current_particle->setStartPxPyPz(start_direction.x(),start_direction.y(),start_direction.z());
    
    // PDG encoding
    int pdg = (int) track->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
    current_particle->setG4Id(pdg);
    
    // start energy
    double start_energy = track->GetKineticEnergy();
    current_particle->setStartE(start_energy);
}

void B1TrackingAction::PostUserTrackingAction(const G4Track* track)
{
    // end position
    G4ThreeVector end_position = track->GetPosition();
    current_particle->setStopXYZ(end_position.x(),end_position.y(),end_position.z());

    // end direction
    G4ThreeVector end_direction = track->GetMomentumDirection();
    current_particle->setStopPxPyPz(end_direction.x(),end_direction.y(),end_direction.z());
    
    // end energy
    if (track->GetKineticEnergy() > 0)
    {
        current_particle->setStopInDetector(false);
    }
    
    // scattering
    TVector3 sta_dir(current_particle->getStartPx(), current_particle->getStartPy(), current_particle->getStartPz());
    TVector3 sto_dir(current_particle->getStopPx(), current_particle->getStopPy(), current_particle->getStopPz());
    Double_t a = sto_dir.Angle(sta_dir);
    a = a *180/TMath::Pi();
    if (a >= 1)
    {
        current_particle->setScattering(true);
    }
    else
    {
        current_particle->setScattering(false);
    }
}
