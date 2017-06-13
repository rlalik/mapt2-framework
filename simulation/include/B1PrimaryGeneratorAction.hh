#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4GeneralParticleSource.hh"
#include "TRandom2.h"
#include "TRandom.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "B1Config.hh"
#include "TMath.h"
#include "TVector3.h"


class G4GeneralParticleSource;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued
/// in front of the phantom across 80% of the (X,Y) phantom size.

class B1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    B1PrimaryGeneratorAction(B1Config* conf);
    virtual ~B1PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);
    void generateFromHisto1 ();
    void generateToMidPoint ();

    // method to access particle gun
    const G4GeneralParticleSource* GetParticleGun() const { return fParticleGun; }

  private:
    G4GeneralParticleSource*  fParticleGun;
    G4ParticleGun* histoGun;

    bool useRootHisto;
    B1Config* config;
    TH1F* energyHisto;
    TH2F* angularHisto;
    Double_t centerMaxRadius;
    Double_t sphereRadius;
    Double_t radiusStart;

    TRandom2 rand_gen;
    TRandom* randomGenerator;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
