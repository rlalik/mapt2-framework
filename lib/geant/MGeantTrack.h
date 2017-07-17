#ifndef MGEANTTRACK_H
#define MGEANTTRACK_H

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
class MGeantTrack : public TObject
{
public:
    MGeantTrack();
    virtual ~MGeantTrack() {}

    void clear();
    void random();                                      // creates a particle with random values for testing
    Double_t getRandomNumber();                          // returns a random number between 0 and 1 (without 0 and 1)
    void addProcess(string name);
    void addDaughterID(Int_t ID);

//     B1DetectorResponse & getDetectorResponse() { return response; }

    TVector3 getStartPosition() const { return startPosition; }
    void setStartPosition(const TVector3 & p) { startPosition = p; }

    TVector3 getEndPosition() const { return endPosition; }
    void setEndPosition(const TVector3 & p) { endPosition = p; }

    Double_t getDistance() const;
    Double_t getRange() const;

    TVector3 getStartDirection() const { return startDirection; }
    void setStartDirection(const TVector3 & p) { startDirection = p; }

    TVector3 getEndDirection() const { return endDirection; }
    void setEndDirection(const TVector3 & p) { endDirection = p; }

    Bool_t getScattering() const { return scattering; }
    void setScattering(Bool_t b) { scattering = b; }

    std::vector<string> getProcesses() const { return processes; }
    void setProcesses(const std::vector<string> & v) { processes = v; }

    Int_t getG4Number() const { return g4Number; }
    void setG4Number(Int_t i) { g4Number = i; }

    Bool_t getStopInDetector() const { return stopInDetector; }
    void setStopInDetector(Bool_t b) { stopInDetector = b; }

    Int_t getTrackID() const { return trackID; }
    void setTrackID(Int_t i) { trackID = i; }
    Int_t getParentID() const { return parentID; }
    void setParentID(Int_t i) { parentID = i; }

    string getGenerationProcess() const { return generationProcess; }
    void setGenerationProcess(string i) { generationProcess = i; }

    Double_t getStartEnergy() const { return startEnergy; }
    void setStartEnergy(Double_t i) { startEnergy = i; }

    Double_t getEndEnergy() const { return endEnergy; }
    void setEndEnergy(Double_t i) { endEnergy = i; }

    void print() const;
    Bool_t isPim() const { return g4Number == -211; }
    Bool_t isPip() const { return g4Number == 211; }
    Bool_t isPiz() const { return g4Number == 111; }
    Bool_t isP() const { return g4Number == 2212; }
    Bool_t isaP() const { return g4Number == -2212; }

    Bool_t getInAcceptance() const { return inAcceptance; }
    void setInAcceptance(Bool_t b) { inAcceptance = b; }

    enum Process { COMPTON, INELASTIC, ATREST };
    void setProcess(Process p) { proc_arr[p] = kTRUE; }
    Bool_t testProcess(Process p) const { return proc_arr[p]; }
    Bool_t isProcessCompton() const { return proc_arr[COMPTON]; }
    Bool_t isProcessInelastic() const { return proc_arr[INELASTIC]; }
    Bool_t isProcessAtRest() const { return proc_arr[ATREST]; }

//     Hits30x30*              getHits()               { return hits; }
//     void setHits(const Hits30x30 & h); 
//     void setHits(const double hitMatrix[30][30]); 

    // Needed for creation of shared library
    ClassDef(MGeantTrack, 1);

private:
    TVector3 startPosition;
    TVector3 endPosition;
    TVector3 startDirection;
    TVector3 endDirection;
    Bool_t scattering;
    std::vector<string> processes;
    Int_t g4Number;
    Bool_t stopInDetector;
    std::vector<Int_t> secondariesID;
    Int_t trackID;
    Int_t parentID;
    string generationProcess;
    Double_t startEnergy;
    Double_t endEnergy;
    Bool_t inAcceptance;

    Bool_t proc_arr[ATREST+1];

//     B1DetectorResponse response;

    TRandom2 randGen;
};

#endif /* MGEANTTRACK_H */
