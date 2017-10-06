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

#ifndef MFIBERSCAL_H
#define MFIBERSCAL_H

#include <TObject.h>

class MFibersCal : public TObject
{
public:
    MFibersCal();
    ~MFibersCal();
    virtual void Clear(Option_t* opt = "");

    void setAddress(Int_t m, Int_t l, Int_t f) { module = m; layer = l; fiber = f; }
    void getAddress(Int_t & m, Int_t & l, Int_t & f) const { m = module; l = layer; f = fiber; }

    void setU(Float_t _u) { u = _u; }
    void setY(Float_t _y) { y = _y; }
    void setEnergyDeposition(Float_t e) { e_dep = e; }
    void addEnergyDeposition(Float_t e) { e_dep += e; }

    Float_t getU() const { return u; }
    Float_t getY() const { return y; }
    Float_t getEnergyDeposition() const { return e_dep; }

    void print() const;

private:
    Int_t module;
    Int_t layer;
    Int_t fiber;

    Float_t u;  // u-coord
    Float_t y;  // y-coord

    Float_t e_dep;  // energy

    ClassDef(MFibersCal, 1);
};

#endif // MFIBERSCAL_H
