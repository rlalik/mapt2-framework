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

#ifndef MDETECTORMANAGER_H
#define MDETECTORMANAGER_H

#include <vector>

#include "MDataManager.h"

class MDetector;

class MDetectorManager
{
private:
    //! \brief Constructor.
    MDetectorManager();
    MDetectorManager(MDetectorManager const &) {}
    MDetectorManager & operator=(MDetectorManager const &) {}

public:
    static MDetectorManager * instance();
    ~MDetectorManager();

    void addDetector(MDetector * detector);

    void initTasks();

    MDataManager * dm() { return MDataManager::instance(); }

private:
    typedef std::vector<MDetector *> DetectorsVec;
    DetectorsVec detectors;

    static MDetectorManager * detm;
};

#endif // MTASKMANAGER_H
