#ifndef EventSim_h
#define EventSim_h

#include <iostream>

#include "TROOT.h"

#include "B1Particle.hh"
#include "B1DetectorResponse.hh"

class TObject;

//! \brief Data structure representing the MC truth of a simulated event.
/*!

*/
class EventSim: public TObject {
public:
    EventSim ();
    ~EventSim ();

    void setPrimary (B1Particle* p) {primary = p;};
    B1Particle* getPrimary () {return primary;};
    void setDetectorResponse (B1DetectorResponse* d) {response = d;};
    B1DetectorResponse* getDetectorResponse () {return response;};
    void setSecondaries (vector<B1Particle*> sec) {secondaries = sec;};
    vector<B1Particle*> getSecondaries () {return secondaries;};
    int getSecondariesMult() { return secondaries.size(); }
    bool isFilled ();                                                       // check if there is data in this object
    void clear ();

    B1Particle* getParticle (int trackID);
    void addSecondaryID(int parentID, int secID);
    void addSecondary(int ID);

    // Needed for creation of shared library
     ClassDef(EventSim, 1);

protected:

private:
    B1Particle* primary;                //->
    vector<B1Particle*> secondaries;    //  not working to read from tree of simulated data
    B1DetectorResponse* response;       //->
};

#endif
