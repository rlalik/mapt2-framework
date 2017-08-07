#ifndef MCATEGORYINDEX_H
#define MCATEGORYINDEX_H

#include <map>

#include <TObject.h>

class MCategoryIndex : public TObject
{
public:
    MCategoryIndex();
    virtual ~MCategoryIndex() {}

    Bool_t setMapIndex(Int_t pos, Int_t val);
    Int_t getMapIndex(Int_t pos);

    Bool_t isCompressed() const { return compressed; }
    size_t size() const { return idxmap.size(); }

    void clear();
    void compress();

private:
    typedef std::map<Int_t, Int_t> IndexMap;
    IndexMap idxmap;
    Bool_t compressed;

    ClassDef(MCategoryIndex, 1);
};

#endif /* MCATEGORYINDEX_H */
