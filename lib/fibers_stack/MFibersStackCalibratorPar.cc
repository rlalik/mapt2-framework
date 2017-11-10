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

#include "MFibersStackCalibratorPar.h"

#include "MParContainer.h"

void MFibersStackCalibratorPar::clear()
{
    fAdcGain = 1.0;
    fAdcOffset = 0.0;
}

bool MFibersStackCalibratorPar::getParams(MParContainer* parcont)
{
    if (!parcont->fill("fAdcGain", fAdcGain)) return false;
    if (!parcont->fill("fAdcOffset", fAdcOffset)) return false;
}

bool MFibersStackCalibratorPar::putParams(MParContainer* parcont) const
{
}

void MFibersStackCalibratorPar::print() const
{
    printf(" +++\n adc gain = %g\n", fAdcGain);
    printf(" adc offset = %g\n", fAdcOffset);
}
