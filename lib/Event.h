#ifndef Event_h
#define Event_h

#include <string>

#include "Hits30x30.h"
#include "EventSim.h"
#include "patternRecognitionData.hh"
#include "analysisData.h"

#include "TROOT.h"
#include "TFile.h"

class TObject;

//! \brief Data structure representing an event.
/*!
  Contains all information of an event. Also the MC truth is saved here.
*/
class Event: public TObject {
public:
    Event ();
    ~Event ();

    Hits30x30*              getHits()               {return hits;};
    EventSim*         getSimulatedEvent ()    {return simData;};
    patternRecognitionData* getPatternRecData ()    {return patternRecData;};
    analysisData*           getFitData ()           {return fitData;};

    void setHits (Hits30x30* h);
    void setHits (double hitMatrix[30][30]);

    bool getIsHits ()       {return isHits;};
    bool getIsSim ()        {return isSim;};
    bool getIsPattern ()    {return isPattern;};
    bool getIsFit ()        {return isFit;};

    void setIsHits (bool b)     {isHits = b;};
    void setIsSim (bool b)      {isSim = b;};
    void setIsPattern (bool b)  {isPattern = b;};
    void setIsFit (bool b)      {isFit = b;};

    void clear ();

    // Needed for creation of shared library
    ClassDef(Event, 2);

protected:

private:
    //! \brief Representing the 900 fiber measurements.
    Hits30x30* hits;

    //! \brief Data from simulation, MC truth  (secondaries cannot be read from simulated data trees).
    EventSim* simData;

    //! \brief Data from pattern recognition.
    patternRecognitionData* patternRecData;

    //! \brief Data from analysis.
    analysisData* fitData;
                
    bool isHits;
    bool isSim;
    bool isPattern;
    bool isFit;
};

#endif
