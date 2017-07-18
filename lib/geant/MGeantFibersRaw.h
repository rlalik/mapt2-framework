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
    void random();

    void Clear(Option_t* options = "");

    void setEnergy(Double_t energy) { energyDeposition = energy; }
    Double_t getEnergy() const { return energyDeposition; }

    void setEnergyQuenching(Double_t energy) { energyDepositionQuenching = energy; }

    void setPhotons(Int_t photon) { opticalPhotonCount += photon; }
    void setTotalEnergy(Double_t e) { totalEnergy += e; }

//     Int_t getFiberHits() const { return fiberHits; }
//     void addFiberHitX() { ++fiberHits_x; ++fiberHits; }
//     Int_t getFiberHitsX() const { return fiberHits_z; }
//     void addFiberHitZ() { ++fiberHits_z; ++fiberHits; }
//     Int_t getFiberHitsZ() const { return fiberHits_z; }

    void setX(Int_t x) { fX = x; }
    void setY(Int_t y) { fY = y; }

    Int_t getX() const { return fX; }
    Int_t getY() const { return fY; }

private:
    Double_t energyDeposition;
    Double_t energyDepositionQuenching;
    Double_t totalEnergy;
    Int_t opticalPhotonCount;
    Int_t fiberHits;
    Int_t fX;
    Int_t fY;

    // Needed for creation of shared library
    ClassDef(MGeantFibersRaw, 1);
};

#endif /* MGEANTFIBERSRAW_H */
