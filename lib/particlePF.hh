#ifndef particlePF_h
#define particlePF_h

#include "TROOT.h"

class TObject;

//! \brief Data structure representing a sample/particle of the particle filter PDF.
/*!
 Needed to save the output of the particle filter. Is just a first prototype and
 not used in the particle filter analysis.
*/
class particlePF: public TObject {
public:
    particlePF ();
    ~particlePF ();

    double weight;
    double pX;
    double pY;
    double pZ;
    double theta;
    double phi;
    double energy;
    void fill (double weight_, double pX_, double pY_, double pZ_, double theta_, double phi_, double energy_);

    // Needed for creation of shared library
     ClassDef(particlePF, 1);

protected:

private:


};

#endif
