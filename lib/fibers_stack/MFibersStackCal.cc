// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include "MFibersStackCal.h"

/** \class MFibersStackCal
\ingroup lib_fibers_stack

A container for Fibers Stack Calibrated data

*/

/** Default constructor
 */
MFibersStackCal::MFibersStackCal() : TObject()
{
    Clear();
}

/** Default destructor
 */
MFibersStackCal::~MFibersStackCal()
{

}

/** Clear object.
 * Parameter options are ignored, for ROOT compatibility.
 * \param opt options
 */
void MFibersStackCal::Clear(Option_t * opt)
{
    module = -1;
    layer = -1;
    fiber = -1;

    u = 0;
    y = 0;
    e_dep = 0.0;
}

/** Print object.
 */
void MFibersStackCal::print() const
{
    printf("fiber m,l,f=%d,%d,%d  u,y=%f,%f  Eloss=%f\n", module, layer, fiber, u, y, e_dep);
}

ClassImp(MFibersStackCal);
