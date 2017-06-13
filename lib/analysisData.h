#ifndef analysisData_h
#define analysisData_h

#include <string>
#include <vector>

#include "TROOT.h"

#include "particlePF.hh"

class TObject;

//! \brief Data structure representing the result of the analysis.
/*!
 This class should hold the PDF of the event. Until now it is a first prototype
 to handle the output of the particle filter. This class has to be defined in the
 future.
*/
class analysisData: public TObject {
public:
    analysisData ();
    ~analysisData ();

    std::vector<particlePF> getPosterior () {return posterior;};
    void fill (double weight, double pX, double pY, double pZ, double theta, double phi, double energy);
    void clear ();

    // Needed for creation of shared library
     ClassDef(analysisData, 1);

protected:

private:
    std::vector<particlePF>  posterior;


};

#endif
