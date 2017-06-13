#include "EventSim.h"

// Needed for Creation of shared libs
ClassImp(EventSim);

EventSim::EventSim () {
    primary = new B1Particle();
    response = new B1DetectorResponse();
}


EventSim::~EventSim() {
    delete primary;
    delete response;
    for (int i=0; i < secondaries.size(); i++) {
        delete secondaries[i];
    }
}

bool EventSim::isFilled () {
    return ((primary != NULL) && (response != NULL));
}

void EventSim::clear () {
    primary->Clear_();
    response->Clear_();

    for (int i=0; i < secondaries.size(); i++) {
        secondaries[i]->Clear_();
        delete secondaries[i];
    }
    secondaries.clear();
}

B1Particle* EventSim::getParticle (int trackID) {
    if (trackID == 1) {
        return primary;
    }
    else {
        for (int i=0; i < secondaries.size(); i++) {
  	         if(secondaries[i]->Get_particle_ID() == trackID) {
  	              return secondaries[i];
              }
  	     }
     }
     std::cerr << "[Error] in EventSim getParticle(int trackID): no Particle with given ID found" << "\n";
     return NULL;
}

void EventSim::addSecondaryID (int parentID, int secID)
{
  B1Particle* particle = getParticle(parentID);
  particle->Add_Daughter_ID (secID);
}

void EventSim::addSecondary (int ID)
{
  B1Particle* particle = new B1Particle();
  particle->Set_particle_ID(ID);
  secondaries.push_back(particle);
}
