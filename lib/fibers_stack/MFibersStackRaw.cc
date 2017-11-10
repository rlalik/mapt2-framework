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

#include "MFibersStackRaw.h"

MFibersStackRaw::MFibersStackRaw() : TObject()
{
    Clear();
}

MFibersStackRaw::~MFibersStackRaw()
{

}

void MFibersStackRaw::Clear(Option_t* )
{
    module = -1;
    layer = -1;
    fiber = -1;

    u = 0;
    y = 0;
    adc = 0.0;
}

void MFibersStackRaw::print() const
{
    printf("fiber m,l,f=%d,%d,%d  u,y=%f,%f  ADC=%f\n", module, layer, fiber, u, y, adc);
}

ClassImp(MFibersStackRaw);
