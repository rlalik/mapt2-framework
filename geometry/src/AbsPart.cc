#include "AbsPart.h"

AbsPart::AbsPart (bool drawable_) {
    drawable = drawable_;
    volumeIndex = -1;
    logical = NULL;
    numberTriangles = -1;
    numberVertices = -1;
}
