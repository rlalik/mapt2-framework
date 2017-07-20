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

#ifndef MFIBERSGEOMPAR_H
#define MFIBERSGEOMPAR_H

#include <TArrayI.h>
#include <TArrayF.h>

#include "MPar.h"

class MFibersGeomPar : public MPar
{
public:
    MFibersGeomPar();
    virtual ~MFibersGeomPar();

    bool getParams(MParContainer * parcont);
    bool putParams(MParContainer * parcont) const;
    void clear();
    void print() const;

    Int_t getModules() const { return modules; }
    Int_t getLayers(Int_t m) const;
    Int_t getFibers(Int_t m, Int_t l) const;
    Float_t getLayerRotation(Int_t m, Int_t l) const;
    Float_t getFiberOffsetX(Int_t m, Int_t l) const;
    Float_t getFiberOffsetY(Int_t m, Int_t l) const;
    Float_t getFibersPitch(Int_t m, Int_t l) const;

private:
    Int_t modules;
    struct SingleModule
    {
        Int_t layers;
        TArrayI fibers;
        TArrayF layer_rotation;
        TArrayF fiber_offset_x;
        TArrayF fiber_offset_y;
        TArrayF fibers_pitch;
    };

    SingleModule * mods;
};

#endif // MFIBERSGEOMPAR_H
