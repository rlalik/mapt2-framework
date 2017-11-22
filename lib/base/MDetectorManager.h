// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MDETECTORMANAGER_H
#define MDETECTORMANAGER_H

#include <vector>

#include "MMAPTManager.h"

class MDetector;

class MDetectorManager
{
private:
    // members
    typedef std::map<std::string, MDetector *> DetectorsMap;    ///< type DetMap
    DetectorsMap detectors;             ///< map detector name to object
    static MDetectorManager * detm;     ///< Instance of the MDetectorManager

private:
    // constructors
    MDetectorManager() {}
    MDetectorManager(MDetectorManager const &) {}

    /// Assignment operator
    /// \return this object
    MDetectorManager & operator=(MDetectorManager const &) { return *this; }

public:
    // instance method
    static MDetectorManager * instance();
    // destructor
    ~MDetectorManager() {}

    // methods
    void addDetector(MDetector * detector);
    MDetector * getDetector(const std::string & name);

    void initTasks();
    void initParameterContainers();
    void initCategories();
};

extern MDetectorManager * dm();

#endif // MTASKMANAGER_H
