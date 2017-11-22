// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#include <iostream>

#include "MDetector.h"

#include "MDetectorManager.h"

/** \class MDetectorManager
\ingroup lib_base

Detector Manager class.

It's a singleton class of which object can be obtained using instance() method.

Each used detector must be registered here using addDetector() method.

After all detectors are add, one can initialzie tasks for all detectors,
parameters, and containers, using following methods:
initTasks(), initParameterContainers(), initCategories().

Particularly, the Parameter Containers must be initialized after the Parameter
Manager MParameterManager as initParameterContainers() checks that all
required parameter containers exists.

*/

MDetectorManager * MDetectorManager::detm = nullptr;

/**
 * Returns instance of the Detector Manager class.
 *
 * \return manager instance
 */
MDetectorManager * MDetectorManager::instance()
{
    if (!detm)
        detm = new MDetectorManager;

    return detm;
}

/** Shortcut
 * \return MDetectorManager instance
 */
MDetectorManager * dm()
{
    return MDetectorManager::instance();
}

/**
 * Add detector.
 *
 * \param detector pointer to a detector object
 */
void MDetectorManager::addDetector(MDetector* detector)
{
    detectors.insert(std::pair<std::string, MDetector*>(detector->GetName(), detector));
    printf("Detector %s add\n", detector->GetName());
}

/**
 * Get detector object by its name.
 *
 * \param name detector name
 * \return pointer to the detector object
 */
MDetector * MDetectorManager::getDetector(const std::string& name)
{
    DetectorsMap::iterator it = detectors.find(name);
    if (it != detectors.end())
        return it->second;
    else
        return nullptr;
}

/**
 * Init all detectors tasks.
 */
void MDetectorManager::initTasks()
{
    for (DetectorsMap::iterator it = detectors.begin(); it != detectors.end(); ++it)
    {
        bool res = it->second->initTasks();

        if (!res)
        {
            std::cerr << "Tasks init failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

/**
 * Init all detectors parameter containers.
 * 
 * It must be called after the MParameterManager has been setup.
 */
void MDetectorManager::initParameterContainers()
{
    for (DetectorsMap::iterator it = detectors.begin(); it != detectors.end(); ++it)
    {
        bool res = it->second->initContainers();

        if (!res)
        {
            std::cerr << "Tasks init failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

/**
 * Init all detectors categories.
 * 
 * It must be called before any detector categor is opened or created. See
 * MMAPTManager and MCategory for details about categories.
 */
void MDetectorManager::initCategories()
{
    for (DetectorsMap::iterator it = detectors.begin(); it != detectors.end(); ++it)
    {
        bool res = it->second->initCategories();

        if (!res)
        {
            std::cerr << "Categories init failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}
