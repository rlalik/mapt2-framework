#include "CADFiber.h"

CADFiber::CADFiber(bool drawable_) : CADPart(drawable_)
{
    midpoint = TVector3 (0,0,0);
    deltaX = 0;
    deltaY = 0;
    deltaZ = 0;
    maxStep = 0;
}

void CADFiber::Init(string path_, string material_, string color_, int number_)
{
    Init (path_, material_, color_);
    number = number_ - 1;

    // generate midpoint and deltas out of vertices -> assumption: Fiber is a quader
    if (drawable)
        calculatePositionAndDeltas();
}

void CADFiber::calculatePositionAndDeltas()
{
    double x1,x2,y1,y2,z1,z2 = 0;

    if (numberVertices == 8)
    {
        x1 = vertices[0].x();
        y1 = vertices[0].y();
        z1 = vertices[0].z();
        for (int i = 0; i < numberVertices; ++i)
        {
            if (x1 != vertices[i].x())
            {
                x2 = vertices[i].x();
            }
            if (y1 != vertices[i].y())
            {
                y2 = vertices[i].y();
            }
            if (z1 != vertices[i].z())
            {
                z2 = vertices[i].z();
            }
        }
        deltaX = TMath::Abs(x1-x2);
        deltaY = TMath::Abs(y1-y2);
        deltaZ = TMath::Abs(z1-z2);

        midpoint.SetX(TMath::Min(x1,x2)+deltaX/2);
        midpoint.SetY(TMath::Min(y1,y2)+deltaY/2);
        midpoint.SetZ(TMath::Min(z1,z2)+deltaZ/2);
    }
}

void CADFiber::setMaxStep(double maxStep_)
{
    maxStep = maxStep_;
    userLimit = new G4UserLimits(maxStep);
    logical->SetUserLimits(userLimit);
}
