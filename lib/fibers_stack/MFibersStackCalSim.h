// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MFIBERSSTACKCALSIM_H
#define MFIBERSSTACKCALSIM_H

#include "MFibersStackCal.h"

class MFibersStackCalSim : public MFibersStackCal
{
protected:
    // data members
    Float_t T;                  ///< kinetic energy
    Float_t E;                  ///< total energy
    Float_t dEdx;               ///< energy loss

public:
    // constructors
    MFibersStackCalSim();
    // detructor
    ~MFibersStackCalSim();

    // inherited from ROOT
    virtual void Clear(Option_t* opt = "");

    // methods
    /// Set kinetic energy
    /// \param t kinetic energy
    void setKineticEnergy(Float_t t) { T = t; }
    /// Get kinetic energy
    /// \return kinetic energy
    Float_t getKineticEnergy() const { return T; }

    /// Set total energy
    /// \param e total energy
    void setTotalEnergy(Float_t e) { E = e; }
    /// Get total energy
    /// \return total energy
    Float_t getTotalEnergy() const { return E; }

    /// Set energy loss
    /// \param e energy loss
    void setEnergyLoss(Float_t e) { dEdx = e; }
    /// Get energy loss
    /// \return energy loss
    Float_t getEnergyLoss() const { return dEdx; }

    void print() const;

private:
    ClassDef(MFibersStackCalSim, 1);
};

#endif // MFIBERSSTACKCALSIM_H
