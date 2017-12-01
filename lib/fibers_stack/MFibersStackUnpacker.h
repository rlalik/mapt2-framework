// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MFIBERSSTACKUNPACKER_H
#define MFIBERSSTACKUNPACKER_H

#include "MTask.h"

class MCategory;
class MFibersStackGeomPar;

class MFibersStackUnpacker : public MTask
{
protected:
    // members
    MCategory * catFibersRaw;           ///< fibers raw category

public:
    // constructor
    MFibersStackUnpacker();
    // destructor
    virtual ~MFibersStackUnpacker();

    // methods
    bool init();
    bool execute();
    bool finalize();
};

#endif // MFIBERSSTACKUNPACKER_H
