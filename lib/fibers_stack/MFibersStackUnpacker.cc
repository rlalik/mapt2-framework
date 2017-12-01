// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include <iostream>

#include "MFibersStackUnpacker.h"
#include "MFibersStackRaw.h"

#include "MParManager.h"
#include "MCategory.h"

/** \class MFibersStackUnpacker
\ingroup lib_fibers_stack

A unpacker task.

\sa MTask
*/

/** Constructor
 */
MFibersStackUnpacker::MFibersStackUnpacker() : MTask(), catFibersRaw(nullptr)
{
}

/** Destructor
 */
MFibersStackUnpacker::~MFibersStackUnpacker()
{
}

/** Init task
 * \sa MTask::init()
 * \return success
 */
bool MFibersStackUnpacker::init()
{
    catFibersRaw = mapt()->buildCategory(MCategory::CatFibersStackRaw);
    if (!catFibersRaw)
    {
        std::cerr << "No CatFibersStackRaw category" << "\n";
        return false;
    }

    return true;
}

/** Execute task
 * \sa MTask::execute()
 * \return success
 */
bool MFibersStackUnpacker::execute()
{
    // get input here

    // determine data size
    int size = 0;

    for (int i = 0; i < size; ++i)
    {
        // do something with the data

        // calculate address
        Int_t mod = 0;
        Int_t lay = 0;
        Int_t fib = 0;

        // take these from lookup table?
        Float_t u = 0;
        Float_t y = 0;

        // take this from data
        Float_t adc = 0;

        MLocator loc(3);
        loc[0] = mod;
        loc[1] = lay;
        loc[2] = fib;

        MFibersStackRaw * pRaw = (MFibersStackRaw *) catFibersRaw->getObject(loc);
        if (!pRaw)
        {
            pRaw = (MFibersStackRaw *) catFibersRaw->getSlot(loc);
            pRaw = new (pRaw) MFibersStackRaw;
        }

        pRaw->setAddress(mod, lay, fib);
        pRaw->setU(u);
        pRaw->setY(y);
        pRaw->setADC(adc);
    }

    return true;
}

/** Finalize task
 * \sa MTask::finalize()
 * \return success
 */
bool MFibersStackUnpacker::finalize()
{
    return true;
}
