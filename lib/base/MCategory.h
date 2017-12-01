// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MCATEGORY_H
#define MCATEGORY_H

#include <TClonesArray.h>
#include <TObject.h>

#include "MCategoryHeader.h"
#include "MCategoryIndex.h"
#include "MLocator.h"

class MCategory : public TObject
{
protected:
    // members
    MCategoryHeader header;     ///< header information
    MCategoryIndex index;       ///< index information
    TClonesArray * data;        ///< data
    ULong_t entries;            ///< number of entries

public:
    /// List of all categories
    enum Cat {
        // simulations
        CatGeantTrack,          ///< geant track
        CatGeantFibersRaw,      ///< fibers hit
        // fibers
        CatFibersStackRaw,      ///< fibers stack raw data
        CatFibersStackCal,      ///< gibers cal data
        CatFiberTrack,          ///< fibers track
        // tracks
        // Limit 
        CatLimitDoNotUse        ///< holds size of the category list
    };

    // constructors
    MCategory();
    MCategory(const char * name, size_t dim, size_t * sizes, bool simulation);
    // destructor
    virtual ~MCategory();

    // methods
//     TObject * operator[](const MLocator & n);
    TObject *& getSlot(const MLocator & n);
    TObject *& getNewSlot();
    TObject * getObject(const MLocator & n);
    TObject * getObject(Int_t i);

    /// Returns name of the container
    /// \return container name
    TString getName() const { return header.name; }

    /// Returns number of entries in the category
    /// \return number of entries
    Int_t getEntries() const { return data->GetEntries(); }

    void compress();

    void clear();
    void print() const;

private:
    void setup(const char * name, size_t dim, size_t * sizes, bool simulation);

    bool checkDim(const MLocator & loc);
    int loc2pos(const MLocator & loc);

private:
    ClassDef(MCategory, 1);
};

#endif /* MCATEGORY_H */
