
#include "B1TrackingAction.hh"
#include "G4DynamicParticle.hh"
#include "G4VProcess.hh"
#include "G4OpticalPhoton.hh"




B1TrackingAction::B1TrackingAction(DataManager* root, B1DetectorConstruction* det)
{
  data_manager = root;
  detector_construction  = det;
}



B1TrackingAction::~B1TrackingAction()
{

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
      current_particle->Set_particle_ID(track_ID);

      // set particle creation process
      current_particle->Set_generation_process("ParticleGun");
    }
  else //secondary
    {
      // current particle is secondary. Add a secondary to event
      current_event->addSecondary(track_ID);

      // Get the pointer to the secondary with the right track ID
      current_particle = current_event->getParticle(track_ID);

      // set particle creation process
      const G4String creator_process_name = track->GetCreatorProcess()->GetProcessName();
      current_particle->Set_generation_process(creator_process_name);

      // Add own ID to parents secondary list
      current_event->addSecondaryID(track->GetParentID(),track_ID);


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
        	detector_response->Set_photons(x_fiber,y_fiber,1);
      }

      ((G4Track*)track)->SetTrackStatus(fStopAndKill);
  }

  // Fill the current particle with information
  // start position
  G4ThreeVector start_position = track->GetPosition();
  TVector3 pos = TVector3(start_position.x(),start_position.y(),start_position.z());
  current_particle->Set_start_position(pos);

  // start direction
  G4ThreeVector start_direction = track->GetMomentumDirection();
  TVector3 dir = TVector3(start_direction.x(),start_direction.y(),start_direction.z());
  current_particle->Set_start_direction(dir);

  // PDG encoding
  int pdg = (int) track->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
  current_particle->Set_geant4_number(pdg);

  // start energy
  double start_energy = track->GetKineticEnergy();
  current_particle->Set_start_energy(start_energy);


}



void B1TrackingAction::PostUserTrackingAction(const G4Track* track)
{
  // end position
  G4ThreeVector end_position = track->GetPosition();
  TVector3 pos = TVector3(end_position.x(),end_position.y(),end_position.z());
  current_particle->Set_end_position(pos);

  // end direction
  G4ThreeVector end_direction = track->GetMomentumDirection();
  TVector3 dir = TVector3(end_direction.x(),end_direction.y(),end_direction.z());
  current_particle->Set_end_direction(dir);

  // end energy
  current_particle->Set_end_energy(track->GetKineticEnergy());
  if (track->GetKineticEnergy() > 0)
  {
      current_particle->Set_stop_in_detector(false);
  }

  // scattering
  Double_t a = dir.Angle(current_particle->Get_start_direction());
  a = a *180/TMath::Pi();
  if (a >= 1)
    {
      current_particle->Set_scattering(true);
    }
  else
    {
      current_particle->Set_scattering(false);
    }


}
