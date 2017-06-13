#include "ParticlePF.hh"

// Needed for Creation of shared libs
ClassImp(ParticlePF);

void ParticlePF::fill(double weight_, double pX_, double pY_, double pZ_, double theta_, double phi_, double energy_)
{
    weight = weight_;
    pX = pX_;
    pY = pY_;
    pZ = pZ_;
    theta = theta_;
    phi = phi_;
    energy = energy_;
}
