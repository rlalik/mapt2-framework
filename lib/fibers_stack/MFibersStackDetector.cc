// @(#)lib/fibers_stack:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include "MFibersStackDetector.h"

#include "MFibersStackGeomPar.h"
#include "MFibersStackCalibratorPar.h"
#include "MFibersStackDigitizerPar.h"

#include "MFibersStackUnpacker.h"
#include "MFibersStackDigitizer.h"

/** \class MFibersStackDetector
\ingroup lib_fibers_stack

An organizer class for the detector

\sa MDetector
*/

/** Constructor
 *
 * \param name detetcor name
 */
MFibersStackDetector::MFibersStackDetector(const std::string & name) : MDetector(name),
modules(1), layers(30), fibers(30)
{
}

/** Constructor
 *
 * \param name detetcor name
 * \param m number of modules
 * \param l number oflayers
 * \param f number of fibers
 */
MFibersStackDetector::MFibersStackDetector(const std::string & name, size_t m, size_t l, size_t f) :
    MDetector(name), modules(m), layers(l), fibers(f)
{
}

/** Destructor
 */
MFibersStackDetector::~MFibersStackDetector()
{
}

/** Init tasks
 *
 * \sa MPar::initTasks()
 * \return success
 */
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

/** Init containers
 *
 * \sa MPar::initCategories()
 * \return success
 */
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

/** Init categries
 *
 * \sa MPar::initCategories()
 * \return success
 */
bool MFibersStackDetector::initCategories()
{
    size_t sizes[3];
    MMAPTManager * dm = MMAPTManager::instance();

    sizes[0] = modules;
    sizes[1] = layers;
    sizes[2] = fibers;
    if (isSimulation())
    {
        size_t sim_sizes[2];
        sim_sizes[0] = modules;
        sim_sizes[1] = layers * fibers;

        if (!dm->registerCategory(MCategory::CatGeantFibersRaw, "MGeantFibersRaw", 2, sim_sizes, true)) return false;
        if (!dm->registerCategory(MCategory::CatFibersStackCal, "MFibersStackCalSim", 3, sizes, true)) return false;
    }
    else
    {
        if (!dm->registerCategory(MCategory::CatFibersStackRaw, "MFibersStackRaw", 3, sizes, true)) return false;
        if (!dm->registerCategory(MCategory::CatFibersStackCal, "MFibersStackCal", 3, sizes, false)) return false;
    }

    return true;
}
