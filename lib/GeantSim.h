#ifndef GEANTSIM_H
#define GEANTSIM_H

#include <iostream>
#include <vector>

#include <TObject.h>

#include "Category.hh"
#include "B1Particle.hh"
#include "Hits30x30.h"

class TObject;

class B1DetectorResponse;

//! \brief Data structure representing the MC truth of a simulated event.
/*!

*/
class GeantSim: public Category
{
public:
    GeantSim();
    virtual ~GeantSim();

    void addTrack(B1Particle* p) { tracks.push_back(p); }
    B1Particle* getTrack(Int_t track_num) const;
    int getTracksMult() const { return tracks.size(); }
/*
    void setDetectorResponse(B1DetectorResponse* d) { response = d; }
    B1DetectorResponse* getDetectorResponse() const { return response; }*/

    bool isFilled() const { return getTracksMult() > 0; }      // check if there is data in this object
    void clear();
    void print() const;

    B1Particle* getParticle(int trackID) const;

    void calcHits();
    Hits30x30<Double_t> getHits() const { return hits; }
    // Needed for creation of shared library
    ClassDef(GeantSim, 1);

private:
    std::vector<B1Particle*> tracks;    //  not working to read from tree of simulated data
    Hits30x30<Double_t> hits;
};

#endif /* GEANTSIM_H */
