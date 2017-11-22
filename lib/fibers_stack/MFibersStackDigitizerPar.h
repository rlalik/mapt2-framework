// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MFIBERSSTACKDIGITIZERPAR_H
#define MFIBERSSTACKDIGITIZERPAR_H

#include "MPar.h"

class MFibersStackDigitizerPar : public MPar
{
protected:
    // members

public:
    // methods
    bool getParams(MParContainer * parcont);
    bool putParams(MParContainer * parcont) const;
    void clear();
};

#endif // MFIBERSSTACKDIGITIZERPAR_H
