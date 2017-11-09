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

#include "MFibersDetector.h"

#include "MFibersGeomPar.h"
#include "MFibersCalibratorPar.h"
#include "MFibersDigitizerPar.h"

#include "MFibersUnpacker.h"
#include "MFibersDigitizer.h"

MFibersDetector::MFibersDetector(const std::string & name) : MDetector(name)
{
}

MFibersDetector::~MFibersDetector()
{
}

bool MFibersDetector::initTasks()
{
    if (isSimulation())
    {
        addTask(new MFibersDigitizer(), 0);
    }
    else
    {
        addTask(new MFibersUnpacker(), 0);
    }

    return true;
}

bool MFibersDetector::initContainers()
{
    pm()->addParameterContainer("MFibersGeomPar",  new MFibersGeomPar());

    if (isSimulation())
    {
        pm()->addParameterContainer("MFibersDigitizerPar",  new MFibersDigitizerPar());
    }
    else
    {
        pm()->addParameterContainer("MFibersCalibratorPar",  new MFibersCalibratorPar());
    }

    return true;
}

bool MFibersDetector::initCategories()
{
    size_t sizes[3];
    MMAPTManager * dm = MMAPTManager::instance();

    sizes[0] = 1;
    sizes[1] = 30;
    sizes[2] = 30;
    if (isSimulation())
    {
        if (!dm->registerCategory(MCategory::CatGeantFibersRaw, "MGeantFibersRaw", 3, sizes, true)) return false;
        if (!dm->registerCategory(MCategory::CatFibersCal, "MFibersCalSim", 3, sizes, true)) return false;
    }
    else
    {
        if (!dm->registerCategory(MCategory::CatFibersRaw, "MFibersRaw", 3, sizes, true)) return false;
        if (!dm->registerCategory(MCategory::CatFibersCal, "MFibersCal", 3, sizes, false)) return false;
    }

    return true;
}
