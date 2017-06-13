#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "Hits30x30.h"
#include "EventSim.h"
#include "PatternRecognitionData.hh"
#include "AnalysisData.h"

#include "TROOT.h"
#include "TFile.h"

class TObject;

//! \brief Data structure representing an event.
/*!
  Contains all information of an event. Also the MC truth is saved here.
*/
class Event: public TObject
{
public:
    Event();
    virtual ~Event();

    Hits30x30*              getHits()               { return hits; }
    EventSim*               getSimulatedEvent()     { return simData; }
    PatternRecognitionData* getPatternRecData()     { return patternRecData; }
    AnalysisData*           getFitData()            { return fitData; }

    void setHits(const Hits30x30 & h);
    void setHits(double hitMatrix[30][30]);

    bool getIsHits()        { return isHits; }
    bool getIsSim()         { return isSim; }
    bool getIsPattern()     { return isPattern; }
    bool getIsFit()         { return isFit; }

    void setIsHits(bool b)      { isHits = b; }
    void setIsSim(bool b)       { isSim = b; }
    void setIsPattern(bool b)   { isPattern = b; }
    void setIsFit(bool b)       { isFit = b; }

    void clear();

    // Needed for creation of shared library
    ClassDef(Event, 2);

private:
    //! \brief Representing the 900 fiber measurements.
    Hits30x30* hits;

    //! \brief Data from simulation, MC truth  (secondaries cannot be read from simulated data trees).
    EventSim* simData;

    //! \brief Data from pattern recognition.
    PatternRecognitionData* patternRecData;

    //! \brief Data from analysis.
    AnalysisData* fitData;
                
    bool isHits;
    bool isSim;
    bool isPattern;
    bool isFit;
};

#endif /* EVENT_H */
