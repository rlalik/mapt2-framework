#include "MGeantFibersRaw.h"

ClassImp(MGeantFibersRaw);

MGeantFibersRaw::MGeantFibersRaw()
{
    clear();
}

void MGeantFibersRaw::clear()
{
    energyDeposition = 0.0;
    energyDepositionQuenching = 0.0;
    opticalPhotonCount = 0;
    
    totalEnergy = 0;
    fiberHits = 0;
    fX = 0;
    fY = 0;
}

void MGeantFibersRaw::random()
{
//     for (int i = 0; i < 30; ++i)
//     {
//         for (int j = 0; j < 30; ++j)
//         {
// //             energyDeposition[i][j]= j*j;
// //             energyDepositionQuenching[i][j]= i*i;
//             opticalPhotonCount[i][j] = j*i;
//         }
//     }
//     
    totalEnergy = 0;
}

void MGeantFibersRaw::Clear(Option_t* options)
{
    clear();
}
