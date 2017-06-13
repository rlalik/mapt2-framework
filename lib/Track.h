#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <vector>

#include <TROOT.h>
#include <TVector3.h>

class TObject;
//! \brief Data structure representing a track found by the pattern recognition.
/*!

*/
class Track: public TObject
{
public:
    Track(const TVector3 & intersectionPoint1_, const TVector3 & intersectionPoint2_);
    virtual ~Track() {};

    // Needed for creation of shared library
     ClassDef(Track, 1);

private:
    TVector3 intersectionPoint1;
    TVector3 intersectionPoint2;
    TVector3 direction;
};

#endif /* TRACK_H */
