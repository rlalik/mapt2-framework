#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

// stl
#include <string>
#include <vector>

// Geant4
#include <globals.hh>
#include <G4VUserDetectorConstruction.hh>

// root

// shared libraries Event.so

// geometry shared library
#include <UserGeant4Geometry.h>

// simulation
#include "B1DetectorConstruction.hh"
#include "B1DetectorResponse.hh"
#include "B1Config.hh"


/// Detector construction class to define materials and geometry.

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    B1DetectorConstruction(B1Config* conf);
    virtual ~B1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    UserGeant4Geometry* getGeo () {return geo;};

private:
      UserGeant4Geometry* geo;
      B1Config* config;
      string geometry_filename;

protected:
      G4LogicalVolume*  fScoringVolume;
};

#endif
