#ifndef CATEGORY_H
#define CATEGORY_H

#include <TClonesArray.h>
#include <TObject.h>

#include "MCategoryHeader.h"
#include "MCategoryIndex.h"
#include "MLocator.h"

class MCategory : public TObject
{
public:
    enum Cat {
        // simulations
        CatGeantTrack,
        CatGeantFibersRaw,
        // fibers
        CatFibersStackRaw,
        CatFibersStackCal,
        CatFiberTrack,
        // tracks
        // Limit 
        CatLimitDoNotUse
    };

    MCategory();
    MCategory(const char * name, size_t dim, size_t * sizes, bool simulation);
    virtual ~MCategory();

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
    void setup(const char * name, size_t dim, size_t * sizes, bool simulation);

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
