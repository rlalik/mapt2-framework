#ifndef B1TrackingAction_h
#define B1TrackingAction_h 1

// stl

// Geant4
#include <globals.hh>
#include <G4LogicalVolume.hh>
#include <G4Track.hh>
#include <G4TrackStatus.hh>
#include <G4UserTrackingAction.hh>
#include <G4DynamicParticle.hh>

// root
#include <TROOT.h>
#include <TVector3.h>
#include <TMath.h>

// shared libraries Event.so
#include <DataManager.hh>
#include <Event.h>
#include <B1Particle.hh>

// geometry shared library
#include <Material.h>
#include <AbsPart.h>
#include <CADFiber.h>


// simulation
#include "B1DetectorConstruction.hh"
#include "B1DetectorResponse.hh"



class G4Track;



class B1TrackingAction : public G4UserTrackingAction
{
  public:
  B1TrackingAction(DataManager* root, B1DetectorConstruction* det);
  ~B1TrackingAction();

  void PreUserTrackingAction(const G4Track* track);
  void PostUserTrackingAction(const G4Track* track);

  private:
  DataManager* data_manager;
  EventSim* current_event;
  B1Particle* current_particle;
  B1DetectorConstruction* detector_construction;
  B1DetectorResponse* detector_response;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
