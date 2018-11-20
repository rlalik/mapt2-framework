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

#include "MTask.h"

#include "MTaskManager.h"

/** \class MParManager
\ingroup lib_base

Task Manager class. Manages all tasks.

It's a singleton class of which object can be obtained using instance() method.

Tasks mamager must be initializatied before MDetectorManager::initTasks()
is called since it adds detector tasks to the manager.

Each tasks is add with given step value. The tasks are executed from step 0
until the last registered step. Tasks at the same step are not guaraneteed to
always execute in the same order. Add tasks at diferent steps to preserve
execution order.
*/

MTaskManager * MTaskManager::tm = nullptr;

/** Returns instance of the Detector Manager class.
 *
 * \return manager instance
 */
MTaskManager * MTaskManager::instance()
{
    if (!tm)
        tm = new MTaskManager;

    return tm;
}

/** Shortcut
 * \return MTaskManager instance
 */
MTaskManager * MAPT::tm()
{
    return MTaskManager::instance();
}

/** Default constructor
 */
MTaskManager::MTaskManager()
{
}

/** Default destructor
 */
MTaskManager::~MTaskManager()
{
}

/** Add task at given step
 * \param task pointer to task object
 * \param step step value
 */
void MTaskManager::addTask(MTask* task, int step)
{
    tasks.insert( std::pair<int, MTask *>(step, task) );
}

/** Init all tasks
 */
void MTaskManager::initTasks()
{
    for (TasksMap::const_iterator it = tasks.begin(); it != tasks.end(); ++it)
    {
        bool res = it->second->init();

        if (!res)
        {
            std::cerr << "Init failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

/** Reinitialize all tasks
 */
void MTaskManager::reinitTasks()
{
    for (TasksMap::const_iterator it = tasks.begin(); it != tasks.end(); ++it)
    {
        bool res = it->second->reinit();

        if (!res)
        {
            std::cerr << "Reinit failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

/** Run tasks.
 *
 * Start with step 0 until the last step.
 */
void MTaskManager::runTasks()
{
    for (TasksMap::const_iterator it = tasks.begin(); it != tasks.end(); ++it)
    {
        bool res = it->second->execute();

        if (!res)
        {
            std::cerr << "Task failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

/** Finalize tasks
 */
void MTaskManager::finalizeTasks()
{
    for (TasksMap::const_iterator it = tasks.begin(); it != tasks.end(); ++it)
    {
        bool res = it->second->finalize();

        if (!res)
        {
            std::cerr << "Finalize failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}
