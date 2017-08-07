#include <iostream>

#include "TClass.h"
#include "TClonesArray.h"

#include "MLocator.h"

// Needed for Creation of shared libs
ClassImp(MLocator);

void MLocator::print() const
{
    printf("Locator: n=%d => ", dim);
    for (int i = 0; i < dim; ++i)
        printf("  %d", addr[i]);
    putchar('\n');
}
