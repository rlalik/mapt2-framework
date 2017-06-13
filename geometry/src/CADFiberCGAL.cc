#include "CADFiberCGAL.h"

CADFiberCGAL::CADFiberCGAL (bool drawable_)
: CADPartCGAL(drawable_) {

}

void CADFiberCGAL::Init (string path_, string material_, string color_, int number_)
{
    Init (path_, material_, color_);
    number = number_;
    // calculate fiberX and fiberY from number
    fiberY = 29 - (number-1)/30;
    fiberX = 29 - (number-1)%30;
}
