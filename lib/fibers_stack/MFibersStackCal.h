// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MFIBERSSTACKCAL_H
#define MFIBERSSTACKCAL_H

#include <TObject.h>

class MFibersStackCal : public TObject
{
protected:
    // data members
    Int_t module;       ///< address - module
    Int_t layer;        ///< address - layer
    Int_t fiber;        ///< address - fiber

    Float_t u;          ///< u-coord
    Float_t y;          ///< y-coord

    Float_t e_dep;      ///< energy deposited

public:
    // constructors
    MFibersStackCal();

    // destructor
    ~MFibersStackCal();

    // inherited from root
    virtual void Clear(Option_t* opt = "");

    // methods
    /// Set address
    /// \param m module
    /// \param l layer
    /// \param f fiber
    void setAddress(Int_t m, Int_t l, Int_t f) { module = m; layer = l; fiber = f; }
    /// Get address
    /// \param m module
    /// \param l layer
    /// \param f fiber
    void getAddress(Int_t & m, Int_t & l, Int_t & f) const { m = module; l = layer; f = fiber; }

    /// Set coordinate along fibers
    /// \param _u transverse coordinate
    void setU(Float_t _u) { u = _u; }
    /// Set coordinate along layers
    /// \param _y longnitudal coordinate
    void setY(Float_t _y) { y = _y; }
    /// Set energy deposition
    /// \param e energy
    void setEnergyDeposition(Float_t e) { e_dep = e; }
    /// Add energy deposition
    /// \param e energy
    void addEnergyDeposition(Float_t e) { e_dep += e; }

    /// Get cooridnate along fibers
    /// \return transverse coordinate
    Float_t getU() const { return u; }
    /// Get cooridnate along layers
    /// \return longnitudal coordinate
    Float_t getY() const { return y; }
    /// Get energy deposition
    /// \return energy
    Float_t getEnergyDeposition() const { return e_dep; }

    void print() const;

    ClassDef(MFibersStackCal, 1);   // container for fibers stack calibrated data
};

#endif // MFIBERSSTACKCAL_H
