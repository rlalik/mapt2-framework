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
#include <iostream>

#include "MFibersGeomPar.h"

#include "MParContainer.h"

MFibersGeomPar::MFibersGeomPar() : MPar(), mods(nullptr)
{
}

MFibersGeomPar::~MFibersGeomPar()
{
    delete [] mods;
}

void MFibersGeomPar::clear()
{
    delete [] mods;
    mods = nullptr;
    modules = 0;
}

bool MFibersGeomPar::getParams(MParContainer* parcont)
{
    if (!parcont->fill("nModules", modules)) return false;

    if (mods) delete [] mods;
    mods = new SingleModule[modules];

    // get layers
    TArrayI _l(modules);
    if (!parcont->fill("nLayers", _l)) return false;
    if (_l.GetSize() != modules)
    {
        std::cerr << "Size of nLayers doesn't match nModules" << std::endl;
        return false;
    }

    int n_layers = _l.GetSum();

    // get fibers
    TArrayI _f(modules*n_layers);
    if (!parcont->fill("nFibers", _f)) return false;
    if (_f.GetSize() != (modules*n_layers))
    {
        std::cerr << "Size of nFibers doesn't match nModules*nLayers" << std::endl;
        return false;
    }

    TArrayF _lr(modules*n_layers);
    if (!parcont->fill("fLayerRotation", _lr)) return false;
    if (_lr.GetSize() != (modules*n_layers))
    {
        std::cerr << "Size of fLayerRotation doesn't match nModules" << std::endl;
        return false;
    }

    TArrayF _fox(modules*n_layers);
    if (!parcont->fill("fFiberOffsetX", _fox)) return false;
    if (_fox.GetSize() != (modules*n_layers))
    {
        std::cerr << "Size of fFiberOffsetX doesn't match nModules" << std::endl;
        return false;
    }

    TArrayF _foy(modules*n_layers);
    if (!parcont->fill("fFiberOffsetY", _foy)) return false;
    if (_foy.GetSize() != (modules*n_layers))
    {
        std::cerr << "Size of fFiberOffsetY doesn't match nModules" << std::endl;
        return false;
    }

    TArrayF _fsp(modules*n_layers);
    if (!parcont->fill("fFibersPitch", _fsp)) return false;
    if (_fsp.GetSize() != (modules*n_layers))
    {
        std::cerr << "Size of fFibersPitch doesn't match nModules" << std::endl;
        return false;
    }

    for (int m = 0; m < modules; ++m)
    {
        mods[m].layers = _l[m];
        mods[m].fibers.Set(mods[m].layers);
        mods[m].layer_rotation.Set(mods[m].layers);
        mods[m].fiber_offset_x.Set(mods[m].layers);
        mods[m].fiber_offset_y.Set(mods[m].layers);
        mods[m].fibers_pitch.Set(mods[m].layers);

        for (int l = 0; l < _l[m]; ++l)
        {
            Int_t fibers = _f[n_layers * m + l];
            Int_t layrot = _lr[n_layers * m + l];
            Float_t fox = _fox[n_layers * m + l];
            Float_t foy = _foy[n_layers * m + l];
            Float_t fsp = _fsp[n_layers * m + l];

            mods[m].fibers[l] = fibers;
            mods[m].layer_rotation[l] = layrot;
            mods[m].fiber_offset_x[l] = fox;
            mods[m].fiber_offset_y[l] = foy;
            mods[m].fibers_pitch[l] = fsp;
        }
    }

    return true;
}

bool MFibersGeomPar::putParams(MParContainer* parcont) const
{
}

void MFibersGeomPar::print() const
{
    printf("Number of modules = %d\n", modules);
    for (int m = 0; m < modules; ++m)
    {
        printf(" +++\n layers = %d\n", mods[m].layers);
        printf(" fibers:");
        for (int l = 0; l < mods[m].layers; ++l)
            printf(" %2d", mods[m].fibers[l]);
        printf("\n layrot:");
        for (int l = 0; l < mods[m].layers; ++l)
            printf(" %2.0f", mods[m].layer_rotation[l]);
        printf("\n  off x:");
        for (int l = 0; l < mods[m].layers; ++l)
            printf(" %2.0f", mods[m].fiber_offset_x[l]);
        printf("\n  off y:");
        for (int l = 0; l < mods[m].layers; ++l)
            printf(" %2.0f", mods[m].fiber_offset_y[l]);
        printf("\n  pitch:");
        for (int l = 0; l < mods[m].layers; ++l)
            printf(" %2.0f", mods[m].fibers_pitch[l]);
        putchar('\n');
    }
}

Int_t MFibersGeomPar::getLayers(Int_t m) const
{
    if (mods and m < modules)
        return mods[m].layers;
    else
        return -1;
}

Int_t MFibersGeomPar::getFibers(Int_t m, Int_t l) const
{
    if (mods and m < modules and l < mods[m].layers)
        return mods[m].fibers[l];
    else
        return -1;
}

Float_t MFibersGeomPar::getLayerRotation(Int_t m, Int_t l) const
{
    if (mods and m < modules and l < mods[m].layers)
        return mods[m].layer_rotation[l];
    else
        return -10000.;
}

Float_t MFibersGeomPar::getFiberOffsetX(Int_t m, Int_t l) const
{
    if (mods and m < modules and l < mods[m].layers)
        return mods[m].fiber_offset_x[l];
    else
        return -10000.;
}

Float_t MFibersGeomPar::getFiberOffsetY(Int_t m, Int_t l) const
{
    if (mods and m < modules and l < mods[m].layers)
        return mods[m].fiber_offset_y[l];
    else
        return -10000.;
}

Float_t MFibersGeomPar::getFibersPitch(Int_t m, Int_t l) const
{
    if (mods and m < modules and l < mods[m].layers)
        return mods[m].fibers_pitch[l];
    else
        return -10000.;
}
