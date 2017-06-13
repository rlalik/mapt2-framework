#include "Event.h"

// Needed for Creation of shared libs
ClassImp(Event);

Event::Event ()
{
    hits = new Hits30x30;
    simData = new EventSim;
    patternRecData = new PatternRecognitionData;
    fitData = new AnalysisData;
    isHits = false;
    isSim = false;
    isPattern = false;
    isFit = false;
}

Event::~Event()
{
    delete fitData;
    delete patternRecData;
    delete simData;
    delete hits;
}

void Event::clear()
{
    hits->clear();
    simData->clear();
    patternRecData->clear();
    fitData->clear();
}

void Event::setHits(const Hits30x30 & h)
{
    hits->set(h);
}

void Event::setHits(double hitMatrix[30][30])
{
    hits->set(hitMatrix);
}
