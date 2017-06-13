#include "AnalysisData.h"

// Needed for Creation of shared libs
ClassImp(AnalysisData);

AnalysisData::AnalysisData()
{
}

void AnalysisData::fill(double weight, double pX, double pY, double pZ, double theta, double phi, double energy)
{
    ParticlePF p;
    p.fill(weight,pX, pY, pZ, theta, phi, energy);
    posterior.push_back(p);
}


void AnalysisData::clear()
{
    posterior.clear();
}
