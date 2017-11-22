// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MFIBERSSTACKCALIBRATOR_H
#define MFIBERSSTACKCALIBRATOR_H

#include "MTask.h"

class MCategory;
class MFibersStackCalibratorPar;

class MFibersStackCalibrator : public MTask
{
protected:
    // members
    MCategory * catFibersRaw;                   ///< fibers raw category
    MCategory * catFibersCal;                   ///< fibers cal category
    MFibersStackCalibratorPar * pCalibratorPar; ///< calibrator parameters

public:
    // constructor
    MFibersStackCalibrator();
    // destructor
    virtual ~MFibersStackCalibrator();

    // methods
    bool init();
    bool execute();
    bool finalize();
};

#endif // MFIBERSSTACKCALIBRATOR_H
