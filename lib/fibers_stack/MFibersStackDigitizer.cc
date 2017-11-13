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

#include "MFibersStackDigitizer.h"
#include "MFibersStackDigitizerPar.h"
#include "MFibersStackGeomPar.h"
#include "MGeantFibersRaw.h"
#include "MFibersStackCalSim.h"

#include "MParManager.h"
#include "MCategory.h"

MFibersStackDigitizer::MFibersStackDigitizer() : MTask(), catGeantFibersRaw(nullptr), pDigiPar(nullptr), pGeomPar(nullptr)
{
}

MFibersStackDigitizer::~MFibersStackDigitizer()
{
}

bool MFibersStackDigitizer::init()
{
    catGeantFibersRaw = dm()->getCategory(MCategory::CatGeantFibersRaw);
    if (!catGeantFibersRaw)
    {
        std::cerr << "No CatGeantFibersRaw category" << "\n";
        return false;
    }

    catFibersCalSim = dm()->buildCategory(MCategory::CatFibersStackCal);
    if (!catFibersCalSim)
    {
        std::cerr << "No CatFibersStackCal category" << "\n";
        return false;
    }

    pGeomPar = (MFibersStackGeomPar*) MParManager::instance()->getParameterContainer("MFibersStackGeomPar");
    if (!pGeomPar)
    {
        std::cerr << "Parameter container 'MFibersStackGeomPar' was not obtained!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return true;
}

bool MFibersStackDigitizer::execute()
{
    int size = catGeantFibersRaw->getEntries();

    for (int i = 0; i < size; ++i)
    {
        MGeantFibersRaw * pHit = (MGeantFibersRaw *)catGeantFibersRaw->getObject(i);
        if (!pHit)
        {
            printf("Hit doesnt exists!\n");
            continue;
        }

        Int_t mod = 0;
        Int_t address = 0;

        pHit->getAddress(mod, address);
        Int_t lay = 0;
        Int_t fib = 0;

        Float_t u = pGeomPar->getFiberOffsetX(mod, lay) + fib * pGeomPar->getFibersPitch(mod, lay);
        Float_t y = pGeomPar->getFiberOffsetY(mod, lay);

        MLocator loc(3);
        loc[0] = mod;
        loc[1] = lay;
        loc[2] = fib;

        MFibersStackCalSim * pCal = (MFibersStackCalSim *) catFibersCalSim->getObject(loc);
        if (!pCal)
        {
            pCal = (MFibersStackCalSim *) catFibersCalSim->getSlot(loc);
            pCal = new (pCal) MFibersStackCalSim;
        }

        pCal->setAddress(mod, lay, fib);
        pCal->setU(u);
        pCal->setY(y);
        pCal->setEnergyLoss(pHit->getEnergyLoss());
        pCal->setEnergyDeposition(pHit->getEnergyDeposition());
        pCal->setKineticEnergy(pHit->getKineticEnergy());
        pCal->setTotalEnergy(pHit->getTotalEnergy());
    }

    return true;
}

bool MFibersStackDigitizer::finalize()
{
    return true;
}
