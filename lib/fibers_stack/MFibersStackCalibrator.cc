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

#include "MFibersStackCalibrator.h"
#include "MFibersStackCalibratorPar.h"
#include "MFibersStackRaw.h"
#include "MFibersStackCal.h"

#include "MParManager.h"
#include "MCategory.h"

/** \class MFibersStackCalibrator
\ingroup lib_fibers_stack

A calibraror task for Fibers Stack.

Takes MGeantFibersStackRaw data and applies calibration. See MTask for the
interface description.

*/

/** Default constructor
 */
MFibersStackCalibrator::MFibersStackCalibrator() : MTask(), catFibersRaw(nullptr), catFibersCal(nullptr), pCalibratorPar(nullptr)
{
}

/** Default destructor
 */
MFibersStackCalibrator::~MFibersStackCalibrator()
{
}

/** Init task
 *
 * \sa MTask::init()
 * \return success
 */
bool MFibersStackCalibrator::init()
{
    // get Raw category
    catFibersRaw = mapt()->getCategory(MCategory::CatFibersStackRaw);
    if (!catFibersRaw)
    {
        std::cerr << "No CatFibersStackRaw category" << "\n";
        return false;
    }

    // create Cal category
    catFibersCal = mapt()->buildCategory(MCategory::CatFibersStackCal);
    if (!catFibersCal)
    {
        std::cerr << "No CatFibersStackCal category" << "\n";
        return false;
    }

    // get calibrator parameters
    pCalibratorPar = (MFibersStackCalibratorPar*) pm()->getParameterContainer("MFibersStackCalibratorPar");
    if (!pCalibratorPar)
    {
        std::cerr << "Parameter container 'MFibersStackCalibratorPar' was not obtained!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return true;
}

/** Execute task
 *
 * \sa MTask::execute()
 * \return success
 */
bool MFibersStackCalibrator::execute()
{
    int size = catFibersRaw->getEntries();

    Float_t adc_gain = pCalibratorPar->getAdcGain();
    Float_t adc_offset = pCalibratorPar->getAdcOffset();

    for (int i = 0; i < size; ++i)
    {
        MFibersStackRaw * pRaw = (MFibersStackRaw *)catFibersRaw->getObject(i);
        if (!pRaw)
        {
            printf("Hit doesnt exists!\n");
            continue;
        }

        Int_t mod = 0;
        Int_t lay = 0;
        Int_t fib = 0;
        pRaw->getAddress(mod, lay, fib);

        // calc laboratory coordinates from digi data
        Float_t u = pRaw->getU();
        Float_t y = pRaw->getY();
        Float_t adc = pRaw->getADC();

        // do your magic here with u, y and adc
        Float_t lab_u = u;
        Float_t lab_y = y;
        Float_t energy = adc_gain * adc + adc_offset;

        MLocator loc(3);
        loc[0] = mod;
        loc[1] = lay;
        loc[2] = fib;

        MFibersStackCal * pCal = (MFibersStackCal *) catFibersCal->getObject(loc);
        if (!pCal)
        {
            pCal = (MFibersStackCal *) catFibersCal->getSlot(loc);
            pCal = new (pCal) MFibersStackCal;
        }

        pCal->setAddress(mod, lay, fib);
        pCal->setU(lab_u);
        pCal->setY(lab_y);
        pCal->setEnergyDeposition(energy);
    }

    return true;
}

/** Finalize task
 *
 * \sa MTask::finalize()
 * \return success
 */
bool MFibersStackCalibrator::finalize()
{
    return true;
}
