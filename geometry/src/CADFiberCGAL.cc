#include "CADFiberCGAL.h"

CADFiberCGAL::CADFiberCGAL (bool drawable_)
: CADPartCGAL(drawable_) {

}

void CADFiberCGAL::Init (string path_, string material_, string color_, int number_)
{
    Init (path_, material_, color_);
    number = number_ - 1;
}
