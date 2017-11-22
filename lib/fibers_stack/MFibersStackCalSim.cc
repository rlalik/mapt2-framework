// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include "MFibersStackCalSim.h"

/** \class MFibersStackCalSim
\ingroup lib_fibers_stack

A container for Fibers Stack Calibrated simulation data

*/

/** Constructor
 */
MFibersStackCalSim::MFibersStackCalSim() : MFibersStackCal(), T(0.0), E(0.0), dEdx(0.0)
{
}

/** Destructor
 */
MFibersStackCalSim::~MFibersStackCalSim()
{
}

/** Clear object.
 * Parameter options are ignored, for ROOT compatibility.
 * \param opt options
 */
void MFibersStackCalSim::Clear(Option_t * opt)
{
    T = 0.0;
    E = 0.0;
    dEdx = 0.0;
}

/** Print category.
 */
void MFibersStackCalSim::print() const
{
    MFibersStackCal::print();
}

ClassImp(MFibersStackCalSim);
