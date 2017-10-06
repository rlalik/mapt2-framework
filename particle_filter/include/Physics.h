#ifndef Physics_h
#define Physics_h

// STL includes
#include <iostream>

// root includes
#include <TVector3.h>
#include <TMath.h>

// MAPT-Analysis framework includes
#include <Material.h>
// includes
#include "RandomGenerator.h"


//! \brief Defines all functions to model physics.
/*!

*/
namespace physics
{
    //! \brief calculates the mean energy loss in a material with CSDA
    double calculateEnergyLossCSDA (double length, double eIn, Material* material);

    //! \brief samples the actual energy loss in a volume
    double sampleEnergyStraggling (double length, double eIn, double energyLoss, Material* material);

    //! \brief samples a change in direction and modifies the direction
    void sampleMultipleScattering (double length, double eIn, TVector3 &direction, Material* material);

    //! \brief returns the maximum range in a material
    double maxRangeInMaterial (double eIn, Material* material);

    //! \brief calculates the mean energy loss in a material with CSDA in backward time direction
    double backCalculateEnergyLossCSDA (double length, double eIn, Material* material);

    //! \brief samples the actual energy loss in a volume backward in time with hit-or-miss algorithm
    double backSampleEnergyStraggling (double length, double eIn, Material* material);

    //! \brief returns the sigma of the energy straggling function (NOT USED)
    double getEnergyStragglingSigma (double length, double eIn, Material* material);


    // old back sample
    // double backSampleEnergyStraggling (double length, double eIn, double eLoss, Material* material);
}

#endif
