#ifndef B1TrackingAction_h
#define B1TrackingAction_h 1

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
class B1EventAction;
class MMAPTManager;
class MGeantTrack;

// geometry shared library
#include <Material.h>
#include <AbsPart.h>
#include <CADFiber.h>

// simulation
#include "B1DetectorConstruction.hh"

class G4Track;

class B1TrackingAction : public G4UserTrackingAction
{
public:
    B1TrackingAction(B1EventAction* eventAction, MMAPTManager* root, B1DetectorConstruction* det);
    virtual ~B1TrackingAction() {}
    
    void PreUserTrackingAction(const G4Track* track);
    void PostUserTrackingAction(const G4Track* track);
    
private:
    B1EventAction*  fEventAction;
    MMAPTManager* data_manager;
    MGeantTrack* current_particle;
    B1DetectorConstruction* detector_construction;
};

#endif
