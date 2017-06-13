#include "Track.h"


Track::Track () {
}

Track::Track (const TVector3 & intersectionPoint1_, const TVector3 & intersectionPoint2_) {
    intersectionPoint1 = intersectionPoint1_;
    intersectionPoint2 = intersectionPoint2_;
}

Track::~Track () {
}
