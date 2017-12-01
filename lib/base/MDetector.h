// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MDETECTOR_H
#define MDETECTOR_H

#include <TNamed.h>

#include "MMAPTManager.h"
#include "MTaskManager.h"
#include "MParManager.h"

class MTask;

class MDetector : public TNamed
{
protected:
    // members
    UInt_t task_mask;       ///< mask on tasks

private:
    // constructor
    MDetector() {};

public:
    // constructor
    MDetector(const std::string & name);
    // destructor
    virtual ~MDetector() {};

    // methods
    /// Initialize tasks
    /// \return success
    virtual bool initTasks() = 0;
    /// Initialize containers
    /// \return success
    virtual bool initContainers() = 0;
    /// Initialize categories
    /// \return success
    virtual bool initCategories() = 0;

    void addTask(MTask * task, Int_t step);

    /** Set tasks mask.
     * When the new task is add, it is logically conjugated with the mask, and
     * if the result is false, task is not add.
     *
     * \param m mask
     */
    void setTaskMask(UInt_t m) { task_mask = m; }
    /// Get tasks mask.
    /// \return tasks mask
    UInt_t getTaskMask() const { return task_mask; }

    /// Is it a simulation run
    /// \return simulation run flag
    bool isSimulation() const { return MMAPTManager::instance()->isSimulation(); }

private:
    ClassDef(MDetector, 1);
};

#endif // MDETECTOR_H
