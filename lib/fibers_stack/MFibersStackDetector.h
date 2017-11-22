// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MFIBERSSTACKDETECTOR_H
#define MFIBERSSTACKDETECTOR_H

#include "MDetector.h"

class MFibersStackDetector : public MDetector
{
protected:
    // members
    const size_t modules;   ///< number of modules
    const size_t layers;    ///< number of layers
    const size_t fibers;    ///< number of fibers

public:
    // constructors
    MFibersStackDetector(const std::string & name);
    MFibersStackDetector(const std::string & name, size_t m, size_t l, size_t f);
    // destructor
    ~MFibersStackDetector();

    // methods
    bool initTasks();
    bool initContainers();
    bool initCategories();
};

#endif // MFIBERSSTACKDETECTOR_H
