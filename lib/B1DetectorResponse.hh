#ifndef B1DETECTORRESPONSE_H
#define B1DETECTORRESPONSE_H

#include "TObject.h"

#include "Hits30x30.h"

//! \brief Data structure representing the detector response in a simulated event.
/*!

*/
class B1DetectorResponse : public TObject
{
public:
    B1DetectorResponse();
    virtual ~B1DetectorResponse() {}
    void clear();
    void random();

    typedef const Double_t (*Arr30x30)[30];

    void setEnergy(Int_t x, Int_t y, Double_t energy) { energyDeposition.addValue(x, y, energy); }
    Double_t getEnergy(Int_t x, Int_t y) const { return energyDeposition.getValue(x, y); }
    Hits30x30<Double_t> getEnergyArray() const { return energyDeposition; }

    void setEnergyQuenching(Int_t x, Int_t y, Double_t energy) { energyDepositionQuenching.addValue(x, y, energy); }

    void setPhotons(Int_t x, Int_t y, Int_t photon) { opticalPhotonCount[x][y] += photon; }
    void setTotalEnergy(Double_t e) { totalEnergy += e; }

    Int_t getFiberHits() const { return fiberHits; }
    void addFiberHitX() { ++fiberHits_x; ++fiberHits; }
    Int_t getFiberHitsX() const { return fiberHits_z; }
    void addFiberHitZ() { ++fiberHits_z; ++fiberHits; }
    Int_t getFiberHitsZ() const { return fiberHits_z; }

private:
    Hits30x30<Double_t> energyDeposition;
    Hits30x30<Double_t> energyDepositionQuenching;
    Double_t totalEnergy;
    Int_t  opticalPhotonCount[30][30];
    Int_t fiberHits;
    Int_t fiberHits_x;
    Int_t fiberHits_z;

    // Needed for creation of shared library
    ClassDef(B1DetectorResponse, 1);
};

#endif /* B1DETECTORRESPONSE_H */
