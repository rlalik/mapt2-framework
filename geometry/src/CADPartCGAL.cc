#include "CADPartCGAL.h"

CADPartCGAL::CADPartCGAL (bool drawable_)
: AbsPartCGAL(drawable_) {

}

void CADPartCGAL::Init (string path_, string material_, string color_)
{
    path = path_;
    materialName = material_;
    color = color_;

    material = new Material ();
    material->Init(materialName,1.0);
}
