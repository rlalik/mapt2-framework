#ifndef MLOCATOR_H
#define MLOCATOR_H

#include <cstddef>
#include <string>
#include <map>

#include <TArrayI.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <TString.h>

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

#endif /* MLOCATOR_H */
