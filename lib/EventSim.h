#ifndef EVENTSIM_H
#define EVENTSIM_H

#include <iostream>
#include <vector>

#include <TObject.h>

class TObject;

class B1Particle;
class B1DetectorResponse;

//! \brief Data structure representing the MC truth of a simulated event.
/*!

*/
class EventSim: public TObject
{
public:
    EventSim();
    virtual ~EventSim();

    void setPrimary(B1Particle* p) { primary = p; }
    B1Particle* getPrimary() const { return primary; }

    void setDetectorResponse(B1DetectorResponse* d) { response = d; }
    B1DetectorResponse* getDetectorResponse() const { return response; }

    void setSecondaries(std::vector<B1Particle*> sec) { secondaries = sec; }
    std::vector<B1Particle*> getSecondaries() const { return secondaries; }

    const B1Particle* getSecondary(int i) const { return (i < getSecondariesMult() ? secondaries[i] : nullptr); }
    int getSecondariesMult() const { return secondaries.size(); }

    bool isFilled() const;      // check if there is data in this object
    void clear();

    B1Particle* getParticle(int trackID) const;
//     void addSecondaryID(int parentID, int secID);
    void addSecondary(B1Particle* sec);

    // Needed for creation of shared library
    ClassDef(EventSim, 1);

private:
    B1Particle* primary;                //->
    std::vector<B1Particle*> secondaries;    //  not working to read from tree of simulated data
    B1DetectorResponse* response;       //->
};

#endif /* EVENTSIM_H */
