#include "MGeantFibersRaw.h"

ClassImp(MGeantFibersRaw);

MGeantFibersRaw::MGeantFibersRaw()
{
    clear();
}

void MGeantFibersRaw::clear()
{
    module = -1;
    fiber = -1;
    energyLoss = 0.0;
    energyDeposition = 0.0;
    energyDepositionQuenching = 0.0;
    opticalPhotonCount = 0;

    totalEnergy = 0.0;
    kineticEnergy = 0.0;
    fiberHits = 0;
}

void MGeantFibersRaw::Clear(Option_t* options)
{
    clear();
}

void MGeantFibersRaw::print() const
{
}
