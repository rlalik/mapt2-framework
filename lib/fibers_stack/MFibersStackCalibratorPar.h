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

#ifndef MFIBERSSTACKCALIBRATORPAR_H
#define MFIBERSSTACKCALIBRATORPAR_H

#include "MPar.h"

class MFibersStackCalibratorPar : public MPar
{
public:
    bool getParams(MParContainer * parcont);
    bool putParams(MParContainer * parcont) const;
    void clear();
    void print() const;

    Int_t getAdcGain() const { return fAdcGain; }
    Int_t getAdcOffset() const { return fAdcOffset; }

private:
    Float_t fAdcGain;
    Float_t fAdcOffset;
};

#endif // MFIBERSSTACKCALIBRATORPAR_H
