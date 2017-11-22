// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MFIBERSSTACKDIGITIZER_H
#define MFIBERSSTACKDIGITIZER_H

#include "MTask.h"

#include <vector>

class MCategory;
class MFibersStackDigitizerPar;
class MFibersStackGeomPar;

class MFibersStackDigitizer : public MTask
{
private:
    // members
    MCategory * catGeantFibersRaw;          ///< genat raw
    MCategory * catFibersCalSim;            ///< fibers cal

    MFibersStackDigitizerPar * pDigiPar;    ///< digitizer parameters
    MFibersStackGeomPar * pGeomPar;         ///< geometry parameters

    std::vector<std::vector<Int_t> > layer_fiber_limit; ///< store fibers offset

public:
    // constructor
    MFibersStackDigitizer();
    // destructor
    virtual ~MFibersStackDigitizer();

    // methods
    bool init();
    bool execute();
    bool finalize();
};

#endif // MFIBERSSTACKDIGITIZER_H
