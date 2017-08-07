#ifndef MCATEGORYHEADER_H
#define MCATEGORYHEADER_H

#include <TArrayI.h>
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

#endif /* MCATEGORYHEADER_H */
