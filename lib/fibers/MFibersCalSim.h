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

#ifndef MFIBERSCALSIM_H
#define MFIBERSCALSIM_H

#include <MFibersCal.h>

class MFibersCalSim : public MFibersCal
{
public:
    MFibersCalSim();
    ~MFibersCalSim();
    virtual void Clear(Option_t* opt = "");

    void setKineticEnergy(Float_t t) { T = t; }
    Float_t getKineticEnergy() const { return T; }

    void setTotalEnergy(Float_t e) { E = e; }
    Float_t getTotalEnergy() const { return E; }

    void setEnergyLoss(Float_t e) { dEdx = e; }
    Float_t getEnergyLoss() const { return dEdx; }

private:
    ClassDef(MFibersCalSim, 1);

    Float_t T;  // kinetic energy
    Float_t E;  // total energy

    Float_t dEdx;  // energy loss
};

#endif // MFIBERSCALSIM_H
