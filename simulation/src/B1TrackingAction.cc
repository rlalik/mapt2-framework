#include "G4DynamicParticle.hh"
#include "G4VProcess.hh"
#include "G4OpticalPhoton.hh"

#include "B1TrackingAction.hh"

#include <DataManager.hh>
#include <Event.h>
#include <EventSim.h>
#include <B1Particle.hh>

B1TrackingAction::B1TrackingAction(DataManager* root, B1DetectorConstruction* det)
{
    data_manager = root;
    detector_construction  = det;
}

void B1TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    // Get pointer to current event
    current_event = data_manager->getEvent()->getSimulatedEvent();
    
    // Get ID of current track
    int track_ID = track->GetTrackID();

    // Decide if this is a primary or a secondary
    if( track_ID  == 1)  // primary
    {
        // current particle is the primary
        current_particle = current_event->getPrimary();
        
        // set current particles ID
        current_particle->setTrackID(track_ID);
        
        // set particle creation process
        current_particle->setGenerationProcess("ParticleGun");
    }
    else //secondary
    {
        current_particle = new B1Particle;
        current_particle->setTrackID(track_ID);
        current_particle->setParentID(track->GetParentID());

        // set particle creation process
        const G4String creator_process_name = track->GetCreatorProcess()->GetProcessName();
        current_particle->setGenerationProcess(creator_process_name);

        // current particle is secondary. Add a secondary to event
        current_event->addSecondary(current_particle);
    }
    
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
        CADFiber* fiber;
        if (fiber = dynamic_cast<CADFiber*> (part))
        {
            detector_response = current_event->getDetectorResponse();
            int x_fiber = fiber->getFiberX();
            int y_fiber = fiber->getFiberY();
            detector_response->setPhotons(x_fiber,y_fiber,1);
        }
        
        ((G4Track*)track)->SetTrackStatus(fStopAndKill);
    }
    
    // Fill the current particle with information
    // start position
    G4ThreeVector start_position = track->GetPosition();
    TVector3 pos = TVector3(start_position.x(),start_position.y(),start_position.z());
    current_particle->setStartPosition(pos);
    
    // start direction
    G4ThreeVector start_direction = track->GetMomentumDirection();
    TVector3 dir = TVector3(start_direction.x(),start_direction.y(),start_direction.z());
    current_particle->setStartDirection(dir);
    
    // PDG encoding
    int pdg = (int) track->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
    current_particle->setG4Number(pdg);
    
    // start energy
    double start_energy = track->GetKineticEnergy();
    current_particle->setStartEnergy(start_energy);
}

void B1TrackingAction::PostUserTrackingAction(const G4Track* track)
{
    // end position
    G4ThreeVector end_position = track->GetPosition();
    TVector3 pos = TVector3(end_position.x(),end_position.y(),end_position.z());
    current_particle->setEndPosition(pos);
    
    // end direction
    G4ThreeVector end_direction = track->GetMomentumDirection();
    TVector3 dir = TVector3(end_direction.x(),end_direction.y(),end_direction.z());
    current_particle->setEndDirection(dir);
    
    // end energy
    if (track->GetKineticEnergy() > 0)
    {
        current_particle->setStopInDetector(false);
    }
    
    // scattering
    Double_t a = dir.Angle(current_particle->getStartDirection());
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
