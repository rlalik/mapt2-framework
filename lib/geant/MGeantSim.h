#ifndef GEANTSIM_H
#define GEANTSIM_H

#include <iostream>
#include <vector>

#include <TObject.h>

#include "MCategory.h"
#include "MGeantTrack.h"
// #include "Hits30x30.h"

class TObject;
class MGeantTrack;

//! \brief Data structure representing the MC truth of a simulated event.
/*!

*/
class MGeantSim: public TObject
{
public:
    MGeantSim();
    virtual ~MGeantSim();

//     bool isFilled() const { return getTracksMult() > 0; }      // check if there is data in this object
    void clear();
    void print() const;

//     void calcHits();
//     Hits30x30<Double_t> getHits() const { return hits; }
    // Needed for creation of shared library

    Float_t cos;
private:
    
    Hits30x30<Double_t> hits;

    ClassDef(MGeantSim, 1);
};

#endif /* GEANTSIM_H */
