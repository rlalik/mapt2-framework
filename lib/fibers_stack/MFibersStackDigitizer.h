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

#ifndef MFIBERSSTACKDIGITIZER_H
#define MFIBERSSTACKDIGITIZER_H

#include "MTask.h"

#include <vector>

class MCategory;
class MFibersStackDigitizerPar;
class MFibersStackGeomPar;

class MFibersStackDigitizer : public MTask
{
public:
    MFibersStackDigitizer();
    virtual ~MFibersStackDigitizer();

    bool init();
    bool execute();
    bool finalize();

private:
    MCategory * catGeantFibersRaw;
    MCategory * catFibersCalSim;

    MFibersStackDigitizerPar * pDigiPar;
    MFibersStackGeomPar * pGeomPar;

    std::vector<std::vector<Int_t> > layer_fiber_limit;
};

#endif // MFIBERSSTACKDIGITIZER_H
