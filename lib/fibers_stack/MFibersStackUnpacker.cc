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

#include "MFibersStackUnpacker.h"
#include "MFibersStackRaw.h"

#include "MParManager.h"
#include "MCategory.h"

MFibersStackUnpacker::MFibersStackUnpacker() : MTask(), catFibersRaw(nullptr)
{
}

MFibersStackUnpacker::~MFibersStackUnpacker()
{
}

bool MFibersStackUnpacker::init()
{
    catFibersRaw = dm()->buildCategory(MCategory::CatFibersStackRaw);
    if (!catFibersRaw)
    {
        std::cerr << "No CatFibersStackRaw category" << "\n";
        return false;
    }

    return true;
}

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

bool MFibersStackUnpacker::finalize()
{
    return true;
}
