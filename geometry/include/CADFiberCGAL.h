#ifndef CADFiberCGAL_h
#define CADFiberCGAL_h

// stl
#include <vector>

// Geant4
#include <G4LogicalVolume.hh>

// root
#include <TVector3.h>
#include <TMath.h>

// geometry shared library
#include "CADPartCGAL.h"

//! \brief Defines a CAD fiber for the geometry representation with CGAL.
/*!
  Defines a CAD fiber. A CAD fiber is a special CADPartCGAL. It adds the additional
  attributes needed to describe a fiber. This includes its x and y position in
  Hits30x30 array and its number, which translates to the x and y position.
*/
class CADFiberCGAL : public CADPartCGAL {
    public:
        //! \brief Constructor.
        /*!
          Sets the default values.
        */
        CADFiberCGAL (bool drawable_);

        //! \brief Destructor. Does nothing.
        ~CADFiberCGAL () {;};

        using CADPartCGAL::Init;
        //! \brief Init function calculates the x and y position in Hits30x30 from the fiber number and calls CADPartCGAL::init.
        void Init (string path_, string material_, string color_, int number_);

        //! \brief Returns x postion in Hits30x30.
        int getFiberX () {return fiberX;};

        //! \brief Returns y postion in Hits30x30.
        int getFiberY () {return fiberY;};

        //! \brief Returns the number of the fiber.
        int getNumber () {return number;};


    private:
        //! \brief X position of the fiber in the Hits30x30 array.
        int fiberX;

        //! \brief Y position of the fiber in the Hits30x30 array.
        int fiberY;

        //! \brief Number of the fiber.
        int number;
};

#endif
