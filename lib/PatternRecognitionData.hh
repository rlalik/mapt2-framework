#ifndef PATTERNRECOGNITIONDATA_H
#define PATTERNRECOGNITIONDATA_H

#include <string>
#include <vector>

#include "TROOT.h"

#include "Track.h"

class TObject;
//! \brief Data structure representing the extracted information of the pattern recognition.
/*!

*/
class PatternRecognitionData: public TObject
{
public:
    PatternRecognitionData() : numberOfTracks(0) {}
    virtual ~PatternRecognitionData() {}

    void addTrack(Track* t);
    void clear();

    // Needed for creation of shared library
    ClassDef(PatternRecognitionData, 2);

private:
    int numberOfTracks;
    std::vector<Track*> tracks;
};

#endif /* PATTERNRECOGNITIONDATA_H */
