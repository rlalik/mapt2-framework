#ifndef ParticleFilter_h
#define ParticleFilter_h

// STL inculdes
#include <vector>
#include <string.h>
#include <iostream>
#include <chrono>

// root includes
#include <TVector3.h>
#include <TRandom.h>
#include <TMath.h>
#include <TSpline.h>
#include "TF1.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TF2.h"
#include "TH2D.h"
#include "TFile.h"
#include <TNtupleD.h>
#include <TVectorD.h>

// geant4 includes

// includes MAPT-Analysis-Framework
#include <AbsPartCGAL.h>
#include <CADFiber.h>
#include <CADFiberCGAL.h>
#include <UserGeant4Geometry.h>
#include <UserCGALGeometry.h>

// includes
#include "Particle.h"
#include "RandomGenerator.h"
#include "Physics.h"

#include "MMAPTManager.h"
#include "MFibersStackCalSim.h"
#include "MFibersStackGeomPar.h"

using namespace std::chrono;

//! \brief The Particle Filter class implementing the particle filter functionalities.
/*!

*/
class ParticleFilter
{
public:
    //! \brief Constructor
    ParticleFilter(UserCGALGeometry* geo,int num);
    //! \brief Destructor
    ~ParticleFilter();

    //! \brief initialize the filter for a event
    bool initEvent(MMAPTManager* event_, double deltaE, double deltaPos, double deltaDir);

    //! \brief generating the particles according to prior
    Particle* generateParticleFromSimulatedEvent(double deltaE, double deltaDir, double deltaPos);

    //! \brief Sample a position with deltaPos around position p
    TVector3 samplePos(TVector3 p, double deltaPos);

    //! \brief Sample a direction with deltaDir around direction p
    TVector3 sampleDir(TVector3 p, double deltaDir);

    //! \brief Sample a start energy
    double sampleE0(double e, double deltaE);

    //! \brief start the forward filter
    bool filter();

    //! \brief propagation (=measurement model) in forward direction
    int propagate(Particle* p, Particle* newParticle, int &volumeIndex);

    //! \brief measurement model
    double evaluate(Particle* p, int volumeIndex);

    //! \brief propagation of physics (=measurement model) in forward direction
    void propagatePhysics(TVector3 &newPIn, TVector3 &newPOut, double &newEIn, double &newEOut, AbsPartCGAL* part);

    // filter backward
    bool backFilter();

    //! \brief propagation (=measurement model) in backward direction
    int backPropagate(Particle* p, Particle* newParticle, int &volumeIndex);

    //! \brief propagation of physics (=measurement model) in backward direction
    void backPropagatePhysics(TVector3 &newPIn, TVector3 &newPOut, double &newEIn, double &newEOut, AbsPartCGAL* part);

    // set functions
    void setNumber(int num) {number = num;};
    void setEvalSigma(double e) {evalSigma = e;};

    //! \brief Perform sampling-importance-resampling
    int sir();
    
    // helper functions
    //! \brief print particles
    void printParticles();

    //! \brief writes marginalized deviation posterior as TH1 to a root file
    void createPosteriors(string path);

    //! \brief writes complete deviation PDF and runtime to a root tree and then to a root file
    void createBackPosteriors(string path, double time);

private:
    //! \brief checks if the particles are initialized
    bool checkVectorSize();

    //! \brief checks if the particles, the geometry, and the event information are initialized
    bool checkInitialisation();

    //! \brief current event (initialized in initEvent)
    MMAPTManager* event;

    //! \brief current hits (initialized in initEvent)
    MCategory* catGeantTrack;
    MCategory* catFibersCal;

    //! \brief geometry representation (initialized in constructor)
    UserCGALGeometry* geometry;

    //! \brief number of particles (initialized in constructor)
    int number;

    //! \brief likelihood sigma (initialized in constructor)
    double evalSigma;

    //! \brief Particles
    vector <Particle*> particles;

    //! \brief temporary particles, needed to copy weights
    vector <Particle*> temps;

    //! \brief weights
    vector <double> weights;

    //! \brief temporary weights, needed to copy weights
    vector <double> tempWeights;

    //! \brief cumulated distribution function needed for sampling new particles according to weights
    vector <double> cdf;

    //! \brief debug level (initialized in constructor)
    int debugLvl;

    MFibersStackGeomPar * pGeomPar;
    std::vector<std::vector<Int_t> > layer_fiber_limit;
};

#endif
