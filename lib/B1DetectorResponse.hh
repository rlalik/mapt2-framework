#ifndef B1DETECTORRESPONSE_H
#define B1DETECTORRESPONSE_H

#include "TObject.h"

//! \brief Data structure representing the detector response in a simulated event.
/*!

*/
class B1DetectorResponse : public TObject
{
public:
    B1DetectorResponse() {}
    virtual ~B1DetectorResponse() {}
    void clear();
    void random();
    void setEnergy(Int_t x, Int_t y, Double_t energy);
    Double_t getEnergy(Int_t x, Int_t y);
    void setEnergyQuenching(Int_t x, Int_t y, Double_t energy);
    void setPhotons(Int_t x, Int_t y, Int_t photon);
    void setTotalEnergy(Double_t e);
    void addFiberHit();
    Int_t getFiberHits();

    Double_t energyDeposition[30][30];
    Double_t energyDepositionQuenching[30][30];
    Double_t totalEnergy;
    Int_t  opticalPhotonCount[30][30];
    Int_t fiberHits;

    // Needed for creation of shared library
    ClassDef(B1DetectorResponse, 1);
};

#endif /* B1DETECTORRESPONSE_H */
