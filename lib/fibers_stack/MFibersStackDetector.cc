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

#include "MFibersStackDetector.h"

#include "MFibersStackGeomPar.h"
#include "MFibersStackCalibratorPar.h"
#include "MFibersStackDigitizerPar.h"

#include "MFibersStackUnpacker.h"
#include "MFibersStackDigitizer.h"

MFibersStackDetector::MFibersStackDetector(const std::string & name) : MDetector(name)
{
}

MFibersStackDetector::~MFibersStackDetector()
{
}

bool MFibersStackDetector::initTasks()
{
    if (isSimulation())
    {
        addTask(new MFibersStackDigitizer(), 0);
    }
    else
    {
        addTask(new MFibersStackUnpacker(), 0);
    }

    return true;
}

bool MFibersStackDetector::initContainers()
{
    pm()->addParameterContainer("MFibersStackGeomPar",  new MFibersStackGeomPar());

    if (isSimulation())
    {
        pm()->addParameterContainer("MFibersStackDigitizerPar",  new MFibersStackDigitizerPar());
    }
    else
    {
        pm()->addParameterContainer("MFibersStackCalibratorPar",  new MFibersStackCalibratorPar());
    }

    return true;
}

bool MFibersStackDetector::initCategories()
{
    size_t sizes[3];
    MMAPTManager * dm = MMAPTManager::instance();

    sizes[0] = 1;
    sizes[1] = 30;
    sizes[2] = 30;
    if (isSimulation())
    {
        if (!dm->registerCategory(MCategory::CatGeantFibersRaw, "MGeantFibersRaw", 3, sizes, true)) return false;
        if (!dm->registerCategory(MCategory::CatFibersStackCal, "MFibersStackCalSim", 3, sizes, true)) return false;
    }
    else
    {
        if (!dm->registerCategory(MCategory::CatFibersStackRaw, "MFibersStackRaw", 3, sizes, true)) return false;
        if (!dm->registerCategory(MCategory::CatFibersStackCal, "MFibersStackCal", 3, sizes, false)) return false;
    }

    return true;
}
