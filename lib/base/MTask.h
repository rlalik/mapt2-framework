// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MTASK_H
#define MTASK_H

#include "MMAPTManager.h"

class MTask
{
public:
    // methods
    /// Initialize task
    /// \return success
    virtual bool init() = 0;
    /// Called when reinitializatoin is required
    /// \return success
    virtual bool reinit() { return true; }
    /// Execute task
    /// \return success
    virtual bool execute() = 0;
    /// Finalize task
    /// \return success
    virtual bool finalize() = 0;
};

#endif // MTASK_H
