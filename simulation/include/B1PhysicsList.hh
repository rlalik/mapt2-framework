
#ifndef B1PhysicsList_h
#define B1PhysicsList_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "B1Config.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4VModularPhysicsList.hh"


class G4VPhysicsConstructor;

class B1PhysicsList: public G4VModularPhysicsList
{
public:
  B1PhysicsList(B1Config* conf);
  ~B1PhysicsList();

protected:
  void SetCuts ();

private:
    B1Config* config;
};


#endif
