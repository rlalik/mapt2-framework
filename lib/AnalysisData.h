#ifndef ANALYSISDATA_H
#define ANALYSISDATA_H

#include <string>
#include <vector>

#include "TROOT.h"

#include "ParticlePF.hh"

class TObject;

//! \brief Data structure representing the result of the analysis.
/*!
 This class should hold the PDF of the event. Until now it is a first prototype
 to handle the output of the particle filter. This class has to be defined in the
 future.
*/
class AnalysisData: public TObject
{
public:
    AnalysisData();
    virtual ~AnalysisData() {}

    std::vector<ParticlePF> getPosterior() { return posterior; }
    void fill(double weight, double pX, double pY, double pZ, double theta, double phi, double energy);
    void clear();

    // Needed for creation of shared library
    ClassDef(AnalysisData, 1);

private:
    std::vector<ParticlePF>  posterior;
};

#endif /* ANALYSISDATA_H */
