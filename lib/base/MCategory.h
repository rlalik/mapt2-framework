#ifndef CATEGORY_H
#define CATEGORY_H

#include <cstddef>
#include <string>
#include <map>

#include <TArrayI.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <TString.h>

///////////////////////////////////////////////////////////////////////////////
// This class allows to map
class MCategoryHeader : public TObject
{
public:
    MCategoryHeader() : TObject() { clear(); }
    virtual ~MCategoryHeader() {}

    TString name;
    Bool_t simulation;
    UInt_t dim;
    TArrayI dim_sizes;
    TArrayI dim_offsets;
    ULong_t data_size;
    Bool_t writable;

    void clear()
    {
        name.Clear();
        simulation = kFALSE;
        dim = 0;
        dim_sizes.Set(0);
        dim_offsets.Set(0);
        data_size = 0;
        writable = kFALSE;
    }

private:
    ClassDef(MCategoryHeader,1);
};

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

class MLocator
{
public:
    MLocator(std::size_t N = 1) : dim(N), addr(N) {}
    virtual ~MLocator() {}

    size_t & operator[](size_t n) { return addr[n]; }
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

    std::size_t getDim() const { return dim; }

    void print() const;

private:
    std::size_t dim;
    std::vector<size_t> addr;

    ClassDef(MLocator, 1);
};

class MCategory : public TObject
{
public:
    enum Cat {
        // simulations
        CatGeantTrack,
        CatGeantFibersRaw,
        // fibers
        CatFibersRaw,
        CatFibersCal,
        CatFiberTrack,
        // tracks
        // Limit 
        CatLimitDoNotUse
    };

    MCategory();
    MCategory(const char * name, size_t dim, size_t * sizes, bool simulation);
    virtual ~MCategory();

    void setup(const char * name, size_t dim, size_t * sizes, bool simulation);

    TObject * operator[](const MLocator & n);
    TObject *& getSlot(const MLocator & n);
    TObject *& getNewSlot();
    TObject * getObject(const MLocator & n);
    TObject * getObject(Int_t i);
    TString getName() const { return header.name; }

    Int_t getEntries() const { return data->GetEntries(); }

    void compress();

    void clear();
    void print() const;

private:
    bool checkDim(const MLocator & loc);
    int loc2pos(const MLocator & loc);

private:
    MCategoryHeader header;
    MCategoryIndex index;
    TClonesArray * data;
    ULong_t entries;

    ClassDef(MCategory, 1);
};

#endif /* CATEGORY_H */
