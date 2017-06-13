#ifndef Track_h
#define Track_h

#include <string>
#include <vector>

#include <TROOT.h>
#include <TVector3.h>

class TObject;
//! \brief Data structure representing a track found by the pattern recognition.
/*!

*/
class Track: public TObject {
public:
    Track ();
    Track (const TVector3 & intersectionPoint1_, const TVector3 & intersectionPoint2_);
    ~Track ();

    // Needed for creation of shared library
     ClassDef(Track, 1);

protected:

private:
    TVector3 intersectionPoint1;
    TVector3 intersectionPoint2;
    TVector3 direction;

    // std::vector<int> fibersOnTrack;

};

#endif
