// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include "MFibersStackRaw.h"

/** \class MFibersStackRaw
\ingroup lib_fibers_stack

A container for Fibers Stack Raw data

*/

/** Constructor
 */
MFibersStackRaw::MFibersStackRaw() : TObject()
{
    Clear();
}

/** Destructor
 */
MFibersStackRaw::~MFibersStackRaw()
{

}

/** Clear object
 * Parameter options are ignored, for ROOT compatibility.
 * \param opt options
 */
void MFibersStackRaw::Clear(Option_t* opt)
{
    module = -1;
    layer = -1;
    fiber = -1;

    u = 0;
    y = 0;
    adc = 0.0;
}

/** Print category
 */
void MFibersStackRaw::print() const
{
    printf("fiber m,l,f=%d,%d,%d  u,y=%f,%f  ADC=%f\n", module, layer, fiber, u, y, adc);
}

ClassImp(MFibersStackRaw);
