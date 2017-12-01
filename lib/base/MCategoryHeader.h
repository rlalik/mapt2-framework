// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MCATEGORYHEADER_H
#define MCATEGORYHEADER_H

#include <TArrayI.h>
#include <TObject.h>
#include <TString.h>

/** \class MCategoryHeader
\ingroup lib_base

A header object for the category

*/

class MCategoryHeader : public TObject
{
public:
    // members
    TString name;           ///< name of the category
    Bool_t simulation;      ///< simulation category
    UInt_t dim;             ///< dimensions
    TArrayI dim_sizes;      ///< dimension sizes
    TArrayI dim_offsets;    ///< dimension offsets
    ULong_t data_size;      ///< data array size
    Bool_t writable;        ///< is writable

public:
    // constructor
    MCategoryHeader() : TObject() { clear(); }
    // Destructor
    virtual ~MCategoryHeader() {}

    /// Clears all members
    void clear();

private:
    ClassDef(MCategoryHeader,1);
};

#endif /* MCATEGORYHEADER_H */
