#include "analysisData.h"

// Needed for Creation of shared libs
ClassImp(analysisData);

analysisData::analysisData () {
    
}


analysisData::~analysisData() {

}


void analysisData::fill (double weight, double pX, double pY, double pZ, double theta, double phi, double energy){
    particlePF p;
    p.fill(weight,pX, pY, pZ, theta, phi, energy);
    posterior.push_back(p);
}


void analysisData::clear() {
    posterior.clear();
}
