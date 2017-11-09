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

#ifndef MFIBERSRAW_H
#define MFIBERSRAW_H

#include <TObject.h>

class MFibersRaw : public TObject
{
public:
    MFibersRaw();
    ~MFibersRaw();
    virtual void Clear(Option_t* opt = "");

    void setAddress(Int_t m, Int_t l, Int_t f) { module = m; layer = l; fiber = f; }
    void getAddress(Int_t & m, Int_t & l, Int_t & f) const { m = module; l = layer; f = fiber; }

    void setU(Float_t _u) { u = _u; }
    void setY(Float_t _y) { y = _y; }
    void setADC(Float_t e) { adc = e; }

    Float_t getU() const { return u; }
    Float_t getY() const { return y; }
    Float_t getADC() const { return adc; }

    void print() const;

private:
    Int_t module;
    Int_t layer;
    Int_t fiber;

    Float_t u;  // u-coord
    Float_t y;  // y-coord

    Float_t adc;  // adc

    ClassDef(MFibersRaw, 1);
};

#endif // MFIBERSRAW_H
