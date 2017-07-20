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

#ifndef MPAR_H
#define MPAR_H

#include "MDataManager.h"

class MParContainer;

class MPar
{
public:
    MPar();
    virtual ~MPar();

    virtual bool getParams(MParContainer * parcont) = 0;
    virtual bool putParams(MParContainer * parcont) const = 0;

    virtual void clear() = 0;
    virtual void print() const;

    MDataManager * dm() { return MDataManager::instance(); }

private:
    MParContainer * parcont;
};

#endif // MPAR_H
