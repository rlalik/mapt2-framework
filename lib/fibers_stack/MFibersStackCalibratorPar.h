// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MFIBERSSTACKCALIBRATORPAR_H
#define MFIBERSSTACKCALIBRATORPAR_H

#include "MPar.h"

class MFibersStackCalibratorPar : public MPar
{
private:
    // members
    Float_t fAdcGain;           ///< ADC gain
    Float_t fAdcOffset;         ///< ADC offset (bias)

public:
    bool getParams(MParContainer * parcont);
    bool putParams(MParContainer * parcont) const;
    void clear();
    void print() const;

    /// Return ADC gain
    /// \return gain
    Int_t getAdcGain() const { return fAdcGain; }
    /// Return ADC offset
    /// \return offset
    Int_t getAdcOffset() const { return fAdcOffset; }
};

#endif // MFIBERSSTACKCALIBRATORPAR_H
