#ifndef Particle_h
#define Particle_h

// STL inculdes
#include <iostream>

// root includes
#include "TVector3.h"

// geant4 includes

// includes MAPT-Analysis-Framework

//! \brief Class representing a sample/particle of the particle filter.
/*!

*/
class Particle {
public:
    Particle ();

    //! \brief Constructor with parameters.
    Particle (TVector3 pIn_, TVector3 pOut_, double eIn_, double eOut_);
    ~Particle ();

    //! \brief Sets new properties to the particle
    void set (TVector3 pIn_, TVector3 pOut_, double eIn_, double eOut_);

    //! \brief Sets new properties to the particle
    void set (Particle* p);

    TVector3 getpIn () {return pIn;};
    TVector3 getpOut () {return pOut;};
    double geteIn () {return eIn;};
    double geteOut () {return eOut;};
    TVector3 getDir ();

    void print ();

    //! \brief Checks if this particle has same properties like the parameter particle p
    bool isSame (Particle* p);


private:
    //! \brief Entry point of current volume.
    TVector3 pIn;

    //! \brief Exit point of current volume.
    TVector3 pOut;

    //! \brief Energy at the entry point.
    double eIn;

    //! \brief Energy at the exit point.
    double eOut;
};

#endif
