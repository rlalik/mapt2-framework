#include "B1DetectorResponse.hh"

// Needed for Creation of shared libs
ClassImp(B1DetectorResponse);

void B1DetectorResponse::clear()
{
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            energyDeposition[i][j] = 0;
            energyDepositionQuenching[i][j] = 0;
            opticalPhotonCount[i][j] = 0;
        }
    }
    
    totalEnergy = 0;
    fiberHits = 0;
    fiberHits_x = 0;
    fiberHits_z = 0;
}


void B1DetectorResponse::random()
{
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            energyDeposition[i][j]= j*j;
            energyDepositionQuenching[i][j]= i*i;
            opticalPhotonCount[i][j] = j*i;
        }
    }
    
    totalEnergy = 0;
}


void B1DetectorResponse::setEnergy(Int_t x, Int_t y, Double_t energy)
{
    energyDeposition[x][y] += energy;
}

void B1DetectorResponse::setEnergyQuenching(Int_t x, Int_t y, Double_t energy)
{
    energyDepositionQuenching[x][y] += energy;
}

void B1DetectorResponse::setPhotons(Int_t x, Int_t y, Int_t photon)
{
    opticalPhotonCount[x][y] += photon;
}

void B1DetectorResponse::setTotalEnergy(Double_t e)
{
    totalEnergy += e;
}

void B1DetectorResponse::addFiberHit()
{
    ++fiberHits;
}

Int_t B1DetectorResponse::getFiberHits()
{
    return fiberHits;
}

Double_t B1DetectorResponse::getEnergy(Int_t x, Int_t y)
{
    return energyDeposition[x][y];
}
