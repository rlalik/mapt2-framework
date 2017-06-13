#include "particlePF.hh"

// Needed for Creation of shared libs
ClassImp(particlePF);

particlePF::particlePF () {
    weight = 0;
}


particlePF::~particlePF() {

}

void particlePF::fill (double weight_, double pX_, double pY_, double pZ_, double theta_, double phi_, double energy_){
    weight = weight_;
    pX = pX_;
    pY = pY_;
    pZ = pZ_;
    theta = theta_;
    phi = phi_;
    energy = energy_;
}
