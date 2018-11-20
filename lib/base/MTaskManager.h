// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MTASKMANAGER_H
#define MTASKMANAGER_H

#include <map>

#include "MMAPTManager.h"

class MTask;

class MTaskManager
{
protected:
    // members
    typedef std::multimap<int, MTask *> TasksMap;   ///< TaskMap type
    TasksMap tasks;                 ///< Tasks map
    static MTaskManager * tm;       ///< Instance of the MTaskManager

private:
    // constructors
    MTaskManager();
    /// Copy constructor
    MTaskManager(MTaskManager const &) {}
    // methods
    /// Assignment operator
    /// \return this object
    MTaskManager & operator=(MTaskManager const &) { return *this; }

public:
    // instance method
    static MTaskManager * instance();
    //destructor
    ~MTaskManager();

    // methods
    void addTask(MTask * task, int step);
    void initTasks();
    void reinitTasks();
    void runTasks();
    void finalizeTasks();
};

namespace MAPT {
    extern MTaskManager * tm();
}

#endif // MTASKMANAGER_H
