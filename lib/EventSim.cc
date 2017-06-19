#include "EventSim.h"

#include "B1Particle.hh"
#include "B1DetectorResponse.hh"

// Needed for Creation of shared libs
ClassImp(EventSim);

EventSim::EventSim()
{
    primary = new B1Particle;
    response = new B1DetectorResponse;
}

EventSim::~EventSim()
{
    delete primary;
    delete response;
    for (int i = 0; i < secondaries.size(); ++i)
    {
        delete secondaries[i];
    }
}

bool EventSim::isFilled() const
{
    return ((primary != NULL) && (response != NULL));
}

void EventSim::clear()
{
    primary->clear();
    response->clear();

    for (int i = 0; i < secondaries.size(); ++i)
    {
        secondaries[i]->clear();
        delete secondaries[i];
    }
    secondaries.clear();
}

B1Particle* EventSim::getParticle(int trackID) const
{
    if (trackID == 1)
        return primary;
    else
    {
        for (int i = 0; i < secondaries.size(); ++i)
        {
            if (secondaries[i]->getTrackID() == trackID) {
                return secondaries[i];
            }
        }
    }
    std::cerr << "[Error] in EventSim getParticle(int trackID): no Particle with given ID found" << "\n";
    return NULL;
}

// void EventSim::addSecondaryID(int parentID, int secID)
// {
//     B1Particle* particle = getParticle(parentID);
//     particle->addDaughterID(secID);
// }

void EventSim::addSecondary(B1Particle* sec)
{
    secondaries.push_back(sec);
}
