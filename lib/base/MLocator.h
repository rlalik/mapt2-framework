// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MLOCATOR_H
#define MLOCATOR_H

#include <cstddef>
#include <string>
#include <map>

#include <TArrayI.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <TString.h>

class MLocator
{
private:
    // members
    std::size_t dim;                ///< dimension of the locator
    std::vector<size_t> addr;       ///< cooridnates of the locator

private:
    // constructor
    MLocator() {}
public:
    // constructor
    /// Constructor
    /// \param N dimension of the locator
    MLocator(std::size_t N) : dim(N), addr(N) {}
    //destructor
    virtual ~MLocator() {}

    //methods

    /// Access coordinate at given position.
    /// \param n dimension position (0..N)
    /// \return coordinate
    size_t & operator[](size_t n) { return addr[n]; }
    /// Same as operator[]()
    /// \param n dimension position (0..N)
    /// \return coordinate
    size_t at(size_t n) const { return addr[n]; }
//     bool operator<(const MLocator & l) const
//     {
//         for (size_t i = 0; i < dim; ++i)
//         {
//             if (addr[i] < l.addr[i])
//                 return true;
//             else if (addr[i] > l.addr[i])
//                 return false;
//         }
// 
//         return false;
//     }
// 
//     bool operator>(const MLocator & l)
//     {
//         return l < *this;
//     }

    /// Get locator dimensions
    /// \return number of dimensions
    std::size_t getDim() const { return dim; }

    void print() const;

private:
    ClassDef(MLocator, 1);
};

#endif /* MLOCATOR_H */
