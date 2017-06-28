#ifndef B1PARTICLE_H
#define B1PARTICLE_H

using namespace std;

//#include "globals.h"
#include <string>
#include <fstream>
#include "TROOT.h"
#include "TRandom2.h"
#include "TVector3.h"

class TObject;

//! \brief Data structure representing a charged particle.
/*!
Represents a charged particle in the Geant4 simulation. Needed to save the MC truth.
*/
class B1Particle : public TObject
{
public:
    B1Particle();
    virtual ~B1Particle() {}

    void clear();
    void random();                                      // creates a particle with random values for testing
    double getRandomNumber();                          // returns a random number between 0 and 1 (without 0 and 1)
    void addProcess(string name);
    void addDaughterID(int ID);

    TVector3 getStartPosition() const { return startPosition; }
    void setStartPosition(const TVector3 & p) { startPosition = p; }

    TVector3 getEndPosition() const { return endPosition; }
    void setEndPosition(const TVector3 & p) { endPosition = p; }

    Double_t getDistance() const;
    Double_t getDepth() const;

    TVector3 getStartDirection() const { return startDirection; }
    void setStartDirection(const TVector3 & p) { startDirection = p; }

    TVector3 getEndDirection() const { return endDirection; }
    void setEndDirection(const TVector3 & p) { endDirection = p; }

    bool getScattering() const { return scattering; }
    void setScattering(bool b) { scattering = b; }

    std::vector<string> getProcesses() const { return processes; }
    void setProcesses(const std::vector<string> & v) { processes = v; }

    int getG4Number() const { return g4Number; }
    void setG4Number(int i) { g4Number = i; }

    bool getStopInDetector() const { return stopInDetector; }
    void setStopInDetector(bool b) { stopInDetector = b; }

    int getTrackID() const { return trackID; }
    void setTrackID(int i) { trackID = i; }
    int getParentID() const { return parentID; }
    void setParentID(int i) { parentID = i; }

    string getGenerationProcess() const { return generationProcess; }
    void setGenerationProcess(string i) { generationProcess = i; }

    double getStartEnergy() const { return startEnergy; }
    void setStartEnergy(double i) { startEnergy = i; }

    double getEndEnergy() const { return endEnergy; }
    void setEndEnergy(double i) { endEnergy = i; }

    void print() const;
    bool isPim() const { return g4Number == -211; }
    bool isPip() const { return g4Number == 211; }
    bool isPiz() const { return g4Number == 111; }
    bool isP() const { return g4Number == 2212; }
    bool isaP() const { return g4Number == -2212; }

    // Needed for creation of shared library
    ClassDef(B1Particle, 1);

private:
    TVector3 startPosition;
    TVector3 endPosition;
    TVector3 startDirection;
    TVector3 endDirection;
    bool scattering;
    std::vector<string> processes;
    int g4Number;
    bool stopInDetector;
    std::vector<int> secondariesID;
    int trackID;
    int parentID;
    string generationProcess;
    double startEnergy;
    double endEnergy;

    TRandom2 randGen;
};

#endif /* B1PARTICLE_H */
