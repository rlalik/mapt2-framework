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

#include "MDetector.h"

#include "MDetectorManager.h"

MDetectorManager * MDetectorManager::detm = nullptr;

MDetectorManager * MDetectorManager::instance()
{
    if (!detm)
        detm = new MDetectorManager;

    return detm;
}

MDetectorManager::MDetectorManager()
{

}

MDetectorManager::~MDetectorManager()
{

}

void MDetectorManager::addDetector(MDetector* detector)
{
    detectors.insert(std::pair<std::string, MDetector*>(detector->GetName(), detector));
    printf("Detector %s add\n", detector->GetName());
}

MDetector * MDetectorManager::getDetector(const std::string& name)
{
    DetectorsMap::iterator it = detectors.find(name);
    if (it != detectors.end())
        return it->second;
    else
        return nullptr;
}

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
