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

#include "MFibersDigitizer.h"
#include "MFibersDigitizerPar.h"
#include "MFibersGeomPar.h"

#include "MParManager.h"
#include "MCategory.h"

MFibersDigitizer::MFibersDigitizer() : MTask(), catGeantFibersRaw(nullptr), pDigiPar(nullptr), pGeomPar(nullptr)
{
}

MFibersDigitizer::~MFibersDigitizer()
{
}

bool MFibersDigitizer::init()
{
    catGeantFibersRaw = dm()->getCategory(MCategory::CatGeantFibersRaw);
    if (!catGeantFibersRaw)
    {
        std::cerr << "No CatGeantFibersRaw category" << "\n";
        return false;
    }

    pGeomPar = (MFibersGeomPar*) MParManager::instance()->getParameterContainer("MFibersGeomPar");
    if (!pGeomPar)
    {
        std::cerr << "Parameter container 'MFibersGeomPar' was not obtained!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return true;
}

bool MFibersDigitizer::execute()
{
//     catGeantFibersRaw->print();
//     pGeomPar->print();
    return true;
}

bool MFibersDigitizer::finalize()
{
    return true;
}
