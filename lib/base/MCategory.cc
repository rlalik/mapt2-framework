#include <iostream>

#include "TClass.h"
#include "TClonesArray.h"

#include "MCategory.h"

// Needed for Creation of shared libs
ClassImp(MCategory);

TObject * pNullMCategoryPtr = nullptr;

MCategory::MCategory() : data(nullptr)
{
    header.clear();
    index.clear();
}

MCategory::MCategory(const char * name, size_t dim, size_t * sizes, bool simulation) : data(nullptr)
{
    header.clear();
    index.clear();
    setup(name, dim, sizes, simulation);

    header.writable = kTRUE;
}

MCategory::~MCategory()
{
    if (data) delete data;
}

void MCategory::setup(const char * name, size_t dim, size_t * sizes, bool simulation)
{
    header.name = name;
    header.dim = dim;
    header.simulation = simulation;
    header.dim_sizes.Set(dim);
    header.dim_offsets.Set(dim);

    header.dim_offsets[0] = 1;
    header.dim_sizes[0] = sizes[0];

    header.data_size = sizes[0];
    for (size_t i = 1; i < dim; ++i)
    {
        header.dim_offsets[i] = header.dim_offsets[i-1] * sizes[i-1];
        header.dim_sizes[i] = sizes[i];
        header.data_size *= sizes[i];
    }

    data = new TClonesArray(name, header.data_size);

    printf("Category %s created with linear size of %d\n", name, header.data_size);
}

TObject * MCategory::operator[](const MLocator & n)
{
    if (!checkDim(header.dim))     return nullptr;

    size_t pos = loc2pos(n);
    Int_t p = index.getMapIndex(pos);
    if (p < 0) return nullptr;
    return data->ConstructedAt(p);
}

TObject *& MCategory::getSlot(const MLocator & n)
{
    if (!checkDim(n))     return pNullMCategoryPtr;

    size_t pos = loc2pos(n);
    if (!index.setMapIndex(pos, pos))
    {
        std::cerr << "Category " << header.name << " was already compressed, can't add new slots." << std::endl;
        return pNullMCategoryPtr;
    }

    if (!getObject(n))  ++entries;

    return data->operator[](pos);
}

TObject *& MCategory::getNewSlot()
{
    if (header.dim != 1)
    {
        std::cerr << "getNewSlot allowed only for linear categories." << std::endl;
        return pNullMCategoryPtr;
    }

    MLocator loc(1);
    loc[0] = data->GetEntries();
    return getSlot(loc);
}

TObject * MCategory::getObject(const MLocator & n)
{
    if (!checkDim(n))     return pNullMCategoryPtr;

    size_t pos = loc2pos(n);
    Int_t p = index.getMapIndex(pos);
    if (p < 0) return nullptr;
    return data->At(p);
}

TObject * MCategory::getObject(Int_t i)
{
    return data->At(i);
}

void MCategory::print() const
{
    printf("Category: %s  length=%d  sim=%d\n", header.name.Data(), header.data_size, header.simulation);
    printf("  index: objects=%d  compressed=%d\n", index.size(), index.isCompressed());
    printf("  %d objects in the category:\n", data->GetEntries());
//     for (size_t i = 0; i < data_size; ++i)
//         printf("[%3d] at 0x%x\n", i, data->At(i));
}

void MCategory::compress()
{
    if (!header.writable)   return;

    data->Compress();
    index.compress();
}

void MCategory::clear()
{
    data->Clear("C");
    index.clear();
}

bool MCategory::checkDim(const MLocator& loc)
{
    if (loc.getDim() != header.dim)
    {
        std::cerr << "Dimension of locator = " << loc.getDim() << " does not fit to category of = " << header.dim << std::endl;
        return false;
    }
    return true;
}


int MCategory::loc2pos(const MLocator& loc)
{
    size_t pos = 0;
    
    for (size_t i = 0; i < header.dim; ++i)
    {//printf("[%d] loc_at=%d   dim_siz=%d\n", i, loc.at(i), header.dim_sizes[i]);
        pos += loc.at(i) * header.dim_offsets[i];
    }//printf("pos=%d\n", pos);
    return pos;
}

// void MCategory::Streamer(TBuffer& R__b)
// {
//     Char_t clase[200];
//     if (R__b.IsReading())
//     {
//         Version_t R__v = R__b.ReadVersion();
//         R__b.ReadString(clase,200);
//         if (data && strcmp(clase, data->GetClass()->GetName()) == 0)
//             data->Clear();
//         else
//         {
//             delete data;
//             data = new TClonesArray(clase);
//         }
//         data->Streamer(R__b);
//     }
//     else
//     {
//         R__b.WriteVersion(MCategory::IsA());
//         strcpy(clase, data->GetClass()->GetName());
//         R__b.WriteString(clase);
//         data->Streamer(R__b);
//     }
// }
