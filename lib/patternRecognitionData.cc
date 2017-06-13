#include "patternRecognitionData.hh"


patternRecognitionData::patternRecognitionData () {
    numberOfTracks = 0;
}


patternRecognitionData::~patternRecognitionData() {

}


void patternRecognitionData::clear () {
    numberOfTracks = 0;
    for (int i=0; i<tracks.size();i++)
    {
        delete tracks[i];
    }
    tracks.clear();
}


void patternRecognitionData::addTrack(Track* t){
    numberOfTracks++;
    tracks.push_back(t);
}
