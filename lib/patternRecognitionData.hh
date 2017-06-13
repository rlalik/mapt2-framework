#ifndef patternRecognitionData_h
#define patternRecognitionData_h

#include <string>
#include <vector>

#include "TROOT.h"

#include "Track.h"

class TObject;
//! \brief Data structure representing the extracted information of the pattern recognition.
/*!

*/
class patternRecognitionData: public TObject {
public:
    patternRecognitionData ();
    ~patternRecognitionData ();

    void addTrack(Track* t);
    void clear ();

    // Needed for creation of shared library
     ClassDef(patternRecognitionData, 2);

protected:

private:
    int numberOfTracks;
    std::vector<Track*> tracks;

};

#endif
