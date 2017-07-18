#include <iostream>

#include "TClass.h"
#include "TClonesArray.h"

#include "MCategory.h"

// Needed for Creation of shared libs
ClassImp(MLocator);
ClassImp(MCategory);

TObject * pNullMCategoryPtr = nullptr;

MCategory::MCategory() : name(""), dim(0), simulation(false), dim_sizes(0), data_size(0), data(nullptr)
{
}

MCategory::MCategory(const char * name, size_t dim, size_t * sizes, bool simulation)
{
    setup(name, dim, sizes, simulation);
}

MCategory::~MCategory()
{
    if (data) delete data;
}

void MCategory::setup(const char * name, size_t dim, size_t * sizes, bool simulation)
{
    this->name = name;
    this->dim = dim;
    this->simulation = simulation;
    dim_sizes.reserve(dim);

    dim_sizes[0] = 1;
    data_size = sizes[0];
    for (size_t i = 1; i < dim; ++i)
    {
        dim_sizes[i] = dim_sizes[i-1] * sizes[i-1];
        data_size *= sizes[i];
    }

    data = new TClonesArray(name, data_size);
    dim_used.reserve(data_size);

    printf("Category %s created with linear size of %ld\n", name, data_size);
}

TObject * MCategory::operator[](const MLocator & n)
{
    if (n.getDim() != dim)
    {
        std::cerr << "Dimension of locator = " << n.getDim() << " does not fit to category of = " << dim << std::endl;
        return nullptr;
    }

    size_t pos = 0;
    
    for (size_t i = 1; i < dim; ++i)
    {
        pos += n.at(i) * dim_sizes[i];
    }
    return data->ConstructedAt(pos);
}

TObject *& MCategory::getSlot(const MLocator & n)
{
    if (n.getDim() != dim)
    {
        std::cerr << "Dimension of locator = " << n.getDim() << " does not fit to category of = " << dim << std::endl;
        return pNullMCategoryPtr;
    }

    size_t pos = 0;
    
    for (size_t i = 0; i < dim; ++i)
    {
        pos += n.at(i) * dim_sizes[i];
    }

    dim_used[pos] = true;
    return data->operator[](pos);
}

TObject *& MCategory::getNewSlot()
{
    if (dim != 1)
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
    if (n.getDim() != dim)
    {
        std::cerr << "Dimension of locator = " << n.getDim() << " does not fit to category of = " << dim << std::endl;
        return pNullMCategoryPtr;
    }

    size_t pos = 0;
    
    for (size_t i = 0; i < dim; ++i)
    {
        pos += n.at(i) * dim_sizes[i];
    }
    return data->At(pos);
}

TObject * MCategory::getObject(Int_t i)
{
    return data->At(i);
}

void MCategory::print() const
{
    printf("%d objects in the category:\n", data->GetEntries());
    for (size_t i = 0; i < data_size; ++i)
    {
//         printf("[%3d] at 0x%x\n", i, data->At(i));
    }
}

void MCategory::Compress()
{
    for (size_t i = 0; i < data_size; ++i)
    {
        if (!dim_used[i])
        {
            (*data)[i] = nullptr;
        }
    }
    data->Compress();
}

void MCategory::clear()
{
    data->Clear("C");
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
