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

#include "MTask.h"

#include "MTaskManager.h"

MTaskManager * MTaskManager::tm = nullptr;

MTaskManager * MTaskManager::instance()
{
    if (!tm)
        tm = new MTaskManager;

    return tm;
}

MTaskManager::MTaskManager()
{

}

MTaskManager::~MTaskManager()
{

}

void MTaskManager::addTask(MTask* task, int step)
{
    tasks.insert( std::pair<int, MTask *>(step, task) );
}

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
