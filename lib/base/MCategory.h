#ifndef CATEGORY_H
#define CATEGORY_H

#include <cstddef>
#include <string>

#include <TClonesArray.h>
#include <TObject.h>

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
        CatFiberTrack
        // tracks
    };

    MCategory();
    MCategory(const char * name, size_t dim, size_t * sizes, bool simulation);
    virtual ~MCategory();

    void setup(const char * name, size_t dim, size_t * sizes, bool simulation);

    TObject * operator[](const MLocator & n);
    TObject *& getSlot(const MLocator & n);
    TObject * getObject(const MLocator & n);
    TObject * getObject(Int_t i);
    std::string getName() const { return name; }

    
    Int_t getEntries() const { return data->GetEntries(); }

    void Compress();

    void print() const;

private:
    std::string name;
    size_t dim;
    bool simulation;
    TClonesArray * data;
    std::vector<size_t> dim_sizes;
    std::vector<bool> dim_used;
    size_t data_size;

    ClassDef(MCategory, 1);
};

#endif /* CATEGORY_H */
