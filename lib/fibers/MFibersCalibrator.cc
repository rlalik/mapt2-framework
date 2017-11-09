/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <iostream>

#include "MFibersCalibrator.h"
#include "MFibersCalibratorPar.h"
#include "MFibersRaw.h"
#include "MFibersCal.h"

#include "MParManager.h"
#include "MCategory.h"

MFibersCalibrator::MFibersCalibrator() : MTask(), catFibersRaw(nullptr), catFibersCal(nullptr), pCalibratorPar(nullptr)
{
}

MFibersCalibrator::~MFibersCalibrator()
{
}

bool MFibersCalibrator::init()
{
    catFibersRaw = dm()->getCategory(MCategory::CatFibersRaw);
    if (!catFibersRaw)
    {
        std::cerr << "No CatFibersRaw category" << "\n";
        return false;
    }

    catFibersCal = dm()->buildCategory(MCategory::CatFibersCal);
    if (!catFibersCal)
    {
        std::cerr << "No CatFibersCal category" << "\n";
        return false;
    }

    pCalibratorPar = (MFibersCalibratorPar*) MParManager::instance()->getParameterContainer("MFibersCalibratorPar");
    if (!pCalibratorPar)
    {
        std::cerr << "Parameter container 'MFibersCalibratorPar' was not obtained!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return true;
}

bool MFibersCalibrator::execute()
{
    int size = catFibersRaw->getEntries();

    Float_t adc_gain = pCalibratorPar->getAdcGain();
    Float_t adc_offset = pCalibratorPar->getAdcOffset();

    for (int i = 0; i < size; ++i)
    {
        MFibersRaw * pRaw = (MFibersRaw *)catFibersRaw->getObject(i);
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

        MFibersCal * pCal = (MFibersCal *) catFibersCal->getObject(loc);
        if (!pCal)
        {
            pCal = (MFibersCal *) catFibersCal->getSlot(loc);
            pCal = new (pCal) MFibersCal;
        }

        pCal->setAddress(mod, lay, fib);
        pCal->setU(lab_u);
        pCal->setY(lab_y);
        pCal->setEnergyDeposition(energy);
    }

    return true;
}

bool MFibersCalibrator::finalize()
{
    return true;
}
