#include "GeantSim.h"

#include "B1Particle.hh"
#include "B1DetectorResponse.hh"

// Needed for Creation of shared libs
ClassImp(GeantSim);

GeantSim::GeantSim() : Category()
{
}

GeantSim::~GeantSim()
{
    for (int i = 0; i < tracks.size(); ++i)
    {
        delete tracks[i];
    }
}

B1Particle * GeantSim::getTrack(Int_t track_num) const
{
    if (track_num < tracks.size())
        return tracks[track_num];
    else
        return nullptr;
}

void GeantSim::clear()
{
    for (int i = 0; i < tracks.size(); ++i)
    {
        tracks[i]->clear();
        delete tracks[i];
    }
    tracks.clear();
}

B1Particle* GeantSim::getParticle(int trackID) const
{
    for (int i = 0; i < tracks.size(); ++i)
    {
        if (tracks[i]->getTrackID() == trackID) {
            return tracks[i];
        }
    }

    std::cerr << "[Error] in GeantSim getParticle(int trackID): no Particle with given ID found" << "\n";
    return nullptr;
}

void GeantSim::calcHits()
{
    hits.clear();
    for (int i = 0; i < tracks.size(); ++i)
    {
        hits += tracks[i]->getDetectorResponse().getEnergyArray();
    }
}

void GeantSim::print() const
{
    printf("Number of tracks = %d\n", tracks.size());
}
