#include "Event.h"

// Needed for Creation of shared libs
ClassImp(Event);

Event::Event () {
    hits = new Hits30x30 ();
    simData = new EventSim();
    patternRecData = new patternRecognitionData();
    fitData = new analysisData();
    isHits = false;
    isSim = false;
    isPattern = false;
    isFit = false;
}


Event::~Event() {
}


void Event::clear () {
    hits->clear();
    simData->clear();
    patternRecData->clear();
    fitData->clear();
}


void Event::setHits (Hits30x30* h) {
    hits->set(h);
}

void Event::setHits (double hitMatrix[30][30]) {
    hits->set(hitMatrix);
}
