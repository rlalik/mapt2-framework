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

    TVector3 getStartPosition() const;
    void setStartPosition(TVector3 p);

    TVector3 getEndPosition() const;
    void setEndPosition(TVector3 p);

    TVector3 getStartDirection() const;
    void setStartDirection(TVector3 p);

    TVector3 getEndDirection() const;
    void setEndDirection(TVector3 p);

    bool getScattering() const;
    void setScattering(bool b);

    std::vector<string> getProcesses() const;
    void setProcesses(const std::vector<string> & v);

    int getG4Number() const;
    void setG4Number(int i);

    bool getStopInDetector() const;
    void setStopInDetector(bool b);

    int getTrackID() const;
    void setTrackID(int i);

    string getGenerationProcess() const;
    void setGenerationProcess(string i);

    double getStartEnergy() const;
    void setStartEnergy(double i);

    double getEndEnergy() const;
    void setEndEnergy(double i);

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
    string generationProcess;
    double startEnergy;
    double endEnergy;

    TRandom2 randGen;
};

#endif /* B1PARTICLE_H */
