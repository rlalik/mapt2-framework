#include <iostream>

#include "TClass.h"
#include "TClonesArray.h"

#include "MCategoryIndex.h"

// Needed for Creation of shared libs
ClassImp(MCategoryIndex);

MCategoryIndex::MCategoryIndex() : TObject(), compressed(kFALSE)
{
    clear();
}

Bool_t MCategoryIndex::setMapIndex(Int_t pos, Int_t val)
{
    if (compressed)
        return kFALSE;

    idxmap[pos] = val;

    return kTRUE;
}

Int_t MCategoryIndex::getMapIndex(Int_t pos)
{
    IndexMap::const_iterator it = idxmap.find(pos);
    if (it == idxmap.end())
        return -1;
    return it->second;
}

void MCategoryIndex::clear()
{
    compressed = kFALSE;
    idxmap.clear();
}

void MCategoryIndex::compress()
{
    Int_t j = 0;
    IndexMap::iterator it = idxmap.begin();
    for (; it != idxmap.end(); ++it)
        it->second = j++;

    compressed = kTRUE;
}
