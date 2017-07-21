#ifndef MGEANTFIBERSRAW_H
#define MGEANTFIBERSRAW_H

#include "TObject.h"

//! \brief Data structure representing the detector response in a simulated event.
/*!

*/
class MGeantFibersRaw : public TObject
{
public:
    MGeantFibersRaw();
    virtual ~MGeantFibersRaw() {}
    void clear();

    void Clear(Option_t* options = "");

    void setEnergy(Double_t energy) { energyDeposition = energy; }
    Double_t getEnergy() const { return energyDeposition; }

    void setEnergyQuenching(Double_t energy) { energyDepositionQuenching = energy; }

    void setPhotons(Int_t photon) { opticalPhotonCount += photon; }
    void setTotalEnergy(Double_t e) { totalEnergy += e; }
    Double_t getTotalEnergy() const { return totalEnergy; }

//     Int_t getFiberHits() const { return fiberHits; }
//     void addFiberHitX() { ++fiberHits_x; ++fiberHits; }
//     Int_t getFiberHitsX() const { return fiberHits_z; }
//     void addFiberHitZ() { ++fiberHits_z; ++fiberHits; }
//     Int_t getFiberHitsZ() const { return fiberHits_z; }

    void setX(Int_t _x) { x = _x; }
    void setY(Int_t _y) { y = _y; }

    Int_t getX() const { return x; }
    Int_t getY() const { return y; }

private:
    Double_t energyDeposition;
    Double_t energyDepositionQuenching;
    Double_t totalEnergy;
    Int_t opticalPhotonCount;
    Int_t fiberHits;
    Int_t x;
    Int_t y;

    // Needed for creation of shared library
    ClassDef(MGeantFibersRaw, 1);
};

#endif /* MGEANTFIBERSRAW_H */
