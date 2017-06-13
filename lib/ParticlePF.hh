#ifndef PARTICLEPF_H
#define PARTICLEPF_H

#include "TROOT.h"

class TObject;

//! \brief Data structure representing a sample/particle of the particle filter PDF.
/*!
 Needed to save the output of the particle filter. Is just a first prototype and
 not used in the particle filter analysis.
*/
class ParticlePF: public TObject
{
public:
    ParticlePF() : weight(0) {}
    virtual ~ParticlePF() {}

    void fill(double weight_, double pX_, double pY_, double pZ_, double theta_, double phi_, double energy_);

    // Needed for creation of shared library
    ClassDef(ParticlePF, 1);

private:
    double weight;
    double pX;
    double pY;
    double pZ;
    double theta;
    double phi;
    double energy;
};

#endif /* PARTICLEPF_H */
