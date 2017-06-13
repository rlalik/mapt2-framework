#include "PatternRecognitionData.hh"

void PatternRecognitionData::clear()
{
    numberOfTracks = 0;
    for (int i=0; i<tracks.size();i++)
    {
        delete tracks[i];
    }
    tracks.clear();
}


void PatternRecognitionData::addTrack(Track* t)
{
    numberOfTracks++;
    tracks.push_back(t);
}
