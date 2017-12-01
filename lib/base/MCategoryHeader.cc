// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include <iostream>

#include "TClass.h"
#include "TClonesArray.h"

#include "MCategoryHeader.h"

void MCategoryHeader::clear()
{
    name.Clear();
    simulation = kFALSE;
    dim = 0;
    dim_sizes.Set(0);
    dim_offsets.Set(0);
    data_size = 0;
    writable = kFALSE;
}

ClassImp(MCategoryHeader);
