// @(#)lib/base:$Id$
// Author: Rafal Lalik  18/11/2017

/*************************************************************************
 * Copyright (C) 2017-2018, Rafał Lalik.                                 *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $MAPTSYS/LICENSE.                         *
 * For the list of contributors see $MAPTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef MCATEGORYINDEX_H
#define MCATEGORYINDEX_H

#include <map>

#include <TObject.h>

class MCategoryIndex : public TObject
{
private:
    // members
    typedef std::map<Int_t, Int_t> IndexMap;    ///< index map type
    IndexMap idxmap;                            ///< map of indexes
    // flags
    Bool_t compressed;                          ///< compressed

public:
    MCategoryIndex();
    virtual ~MCategoryIndex() {}

    Bool_t setMapIndex(Int_t pos, Int_t val);
    Int_t getMapIndex(Int_t pos);

    /// Is category compressed already
    /// \return compressed
    Bool_t isCompressed() const { return compressed; }
    /// Get number of categories
    /// \return number
    size_t size() const { return idxmap.size(); }

    void clear();
    void compress();

    ClassDef(MCategoryIndex, 1);
};

#endif /* MCATEGORYINDEX_H */
