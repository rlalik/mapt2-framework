// @(#)lib/geant:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include "MGeantFibersRaw.h"

/** \class MGeantFibersRaw
\ingroup lib_geant

A container for Geant Fiber hits

*/

/** Constructor
 */
MGeantFibersRaw::MGeantFibersRaw()
{
    clear();
}

/** Clear container
 */
void MGeantFibersRaw::clear()
{
    module = -1;
    fiber = -1;
    energyLoss = 0.0;
    energyDeposition = 0.0;
    energyDepositionQuenching = 0.0;
    opticalPhotonCount = 0;

    totalEnergy = 0.0;
    kineticEnergy = 0.0;
    fiberHits = 0;
}

/** Clear object
 * Parameter options are ignored, for ROOT compatibility.
 * \param opt options
 */
void MGeantFibersRaw::Clear(Option_t* opt)
{
    clear();
}

/** Print container
 */
void MGeantFibersRaw::print() const
{
}

ClassImp(MGeantFibersRaw);
