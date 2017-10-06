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

#ifndef MPARMANAGER_H
#define MPARMANAGER_H

#include <map>

#include "MDataManager.h"

class MParContainer;
class MPar;

class MParManager
{
private:
    //! \brief Constructor.
    MParManager();
    MParManager(MParManager const &) {}
    MParManager & operator=(MParManager const &) { return *this; }

public:
    static MParManager * instance();
    ~MParManager();

    void setParamSource(const std::string & source) { this->source = source; }
    void setParamDest(const std::string & dest) { this->destination = dest; }

    bool parseSource();
    void writeDestination() const;

    bool addParameterContainer(const std::string & cont_name, MPar * parcont);
    MPar * getParameterContainer(const std::string & cont_name);

    void print() const;
private:
    enum WhatNext { WNContainer, WNContainerOrParam, WNParam, WNParamCont };
    WhatNext parseValues(const std::string & str, std::vector<std::string> & values);

    std::string source;
    std::string destination;

    std::map<std::string, MParContainer *> containers;
    std::map<std::string, MPar *> parconts;

    static MParManager * tm;
};

#endif // MPARMANAGER_H
