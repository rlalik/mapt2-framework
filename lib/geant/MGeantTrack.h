#ifndef MGEANTTRACK_H
#define MGEANTTRACK_H

using namespace std;

//#include "globals.h"
#include <string>
#include <fstream>
#include "TObject.h"
#include "TRandom2.h"
#include "TVector3.h"

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
    void addProcess(string name);
    void addDaughterID(Int_t ID);

    void setStartXYZ(Float_t x, Float_t y, Float_t z) { start.x = x; start.y = y; start.z = z; }
    Float_t getStartX() const { return start.x; }
    Float_t getStartY() const { return start.y; }
    Float_t getStartZ() const { return start.z; }

    void setStartPxPyPz(Float_t px, Float_t py, Float_t pz) { start.px = px; start.py = py; start.pz = pz; }
    Float_t getStartPx() const { return start.px; }
    Float_t getStartPy() const { return start.py; }
    Float_t getStartPz() const { return start.pz; }

    void setStartE(Float_t e) { start.E = e; }
    Float_t getStartE() const { return start.E; }

    void setStopXYZ(Float_t x, Float_t y, Float_t z) { stop.x = x; stop.y = y; stop.z = z; }
    Float_t getStopX() const { return stop.x; }
    Float_t getStopY() const { return stop.y; }
    Float_t getStopZ() const { return stop.z; }

    void setStopPxPyPz(Float_t px, Float_t py, Float_t pz) { stop.px = px; stop.py = py; stop.pz = pz; }
    Float_t getStopPx() const { return stop.px; }
    Float_t getStopPy() const { return stop.py; }
    Float_t getStopPz() const { return stop.pz; }

    void setStopE(Float_t e) { stop.E = e; }
    Float_t getStopE() const { return stop.E; }

    Double_t getDistance() const;
    Double_t getRange() const;

    Bool_t getScattering() const { return scattering; }
    void setScattering(Bool_t b) { scattering = b; }

    std::vector<string> getProcesses() const { return processes; }
    void setProcesses(const std::vector<string> & v) { processes = v; }

    Int_t getG4Id() const { return g4Id; }
    void setG4Id(Int_t i) { g4Id = i; }

    Bool_t getStopInDetector() const { return stopInDetector; }
    void setStopInDetector(Bool_t b) { stopInDetector = b; }

    Int_t getTrackID() const { return trackID; }
    void setTrackID(Int_t i) { trackID = i; }
    Int_t getParentID() const { return parentID; }
    void setParentID(Int_t i) { parentID = i; }

    string getGenerationProcess() const { return generationProcess; }
    void setGenerationProcess(string i) { generationProcess = i; }

    void print() const;
    Bool_t isPim() const { return g4Id == -211; }
    Bool_t isPip() const { return g4Id == 211; }
    Bool_t isPiz() const { return g4Id == 111; }
    Bool_t isP() const { return g4Id == 2212; }
    Bool_t isaP() const { return g4Id == -2212; }

    Bool_t getInAcceptance() const { return inAcceptance; }
    void setInAcceptance(Bool_t b) { inAcceptance = b; }

    enum Process { COMPTON, INELASTIC, ATREST };
    void setProcess(Process p) { proc_arr[p] = kTRUE; }
    Bool_t testProcess(Process p) const { return proc_arr[p]; }
    Bool_t isProcessCompton() const { return proc_arr[COMPTON]; }
    Bool_t isProcessInelastic() const { return proc_arr[INELASTIC]; }
    Bool_t isProcessAtRest() const { return proc_arr[ATREST]; }

    void Clear(Option_t * options = "");
//     Hits30x30*              getHits()               { return hits; }
//     void setHits(const Hits30x30 & h); 
//     void setHits(const double hitMatrix[30][30]); 

    // Needed for creation of shared library
    ClassDef(MGeantTrack, 1);

private:
    struct Point {
        Float_t x, y, z;
        Float_t px, py, pz;
        Float_t E;
    } start, stop;
    Bool_t scattering;
    std::vector<string> processes;
    Int_t g4Id;
    Bool_t stopInDetector;
    std::vector<Int_t> secondariesID;
    Int_t trackID;
    Int_t parentID;
    string generationProcess;
    Bool_t inAcceptance;

    Bool_t proc_arr[ATREST+1];

//     B1DetectorResponse response;

    TRandom2 randGen;
};

#endif /* MGEANTTRACK_H */
