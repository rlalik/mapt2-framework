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

    void setEnergyLoss(Double_t energy) { energyLoss = energy; }
    void addEnergyLoss(Double_t energy) { energyLoss += energy; }
    Double_t getEnergyLoss() const { return energyLoss; }

    void setEnergyDeposition(Double_t energy) { energyDeposition = energy; }
    void addEnergyDeposition(Double_t energy) { energyDeposition += energy; }
    Double_t getEnergyDeposition() const { return energyDeposition; }

    void setEnergyQuenching(Double_t energy) { energyDepositionQuenching = energy; }

    void setPhotons(Int_t photon) { opticalPhotonCount += photon; }
    void setTotalEnergy(Double_t e) { totalEnergy += e; }
    Double_t getTotalEnergy() const { return totalEnergy; }
    void setKineticEnergy(Double_t e) { kineticEnergy += e; }
    Double_t getKineticEnergy() const { return kineticEnergy; }

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
    Double_t energyLoss;
    Double_t energyDeposition;
    Double_t energyDepositionQuenching;
    Double_t totalEnergy;
    Double_t kineticEnergy;
    Int_t opticalPhotonCount;
    Int_t fiberHits;
    Int_t x;
    Int_t y;

    // Needed for creation of shared library
    ClassDef(MGeantFibersRaw, 1);
};

#endif /* MGEANTFIBERSRAW_H */
