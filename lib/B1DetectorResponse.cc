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
