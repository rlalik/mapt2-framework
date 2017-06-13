#ifndef CADFiber_h
#define CADFiber_h

// stl
#include <vector>

// Geant4
#include <G4LogicalVolume.hh>
#include "G4UserLimits.hh"

// root
#include <TVector3.h>
#include <TMath.h>

// geometry shared library
#include "CADPart.h"


//! \brief Defines a CAD fiber for the geometry representation with Geant4.
/*!
  Defines a CAD fiber. A CAD fiber is a special CADPart. It adds the additional
  attributes needed to describe a fiber. This includes its x and y position in
  Hits30x30 array and its number, which translates to the x and y position.
  Further the CAD information can be used to generate all information needed to
  describe the fiber as a quader. With this information we can implement the fiber
  as a G4Box in CSG geometry. This can improve the computational performance.
  Further studies are needed for this.
*/
class CADFiber : public CADPart {
    public:
        //! \brief Constructor.
        /*!
          Sets the default values.
        */
        CADFiber (bool drawable_);

        //! \brief Destructor. Does nothing.
        ~CADFiber () {;};

        using CADPart::Init;
        //! \brief Init function calculates the x and y position in Hits30x30 from the fiber number and calls CADPart::init.
        void Init (string path_, string material_, string color_, int number_);

        //! \brief Returns x postion in Hits30x30.
        int getFiberX () {return fiberX;};

        //! \brief Returns y postion in Hits30x30.
        int getFiberY () {return fiberY;};

        //! \brief Returns the number of the fiber.
        int getNumber () {return number;};

        //! \brief Returns the midpoint (=geometric center) of the fiber.
        TVector3 getMidpoint () {return midpoint;};


        double getDeltaX () {return deltaX;};
        double getDeltaY () {return deltaY;};
        double getDeltaZ () {return deltaZ;};

        //! \brief Sets the Steplimiter and assigns it to the G4LogicalVolume of this detector part.
        void setMaxStep (double maxStep_);

    private:
        //! \brief Calculates geometric properties of the fiber to use it in CSG geometry.
        void calculatePositionAndDeltas ();

        //! \brief Maximal step size in a fiber used by Geant4 simulations.
        double maxStep;

        //! \brief Steplimiter for Geant4 simulations.
        G4UserLimits* userLimit;

        //! \brief X position of the fiber in the Hits30x30 array.
        int fiberX;

        //! \brief Y position of the fiber in the Hits30x30 array.
        int fiberY;

        //! \brief Number of the fiber.
        int number;

        //! \brief Geometric center of the fiber.
        TVector3 midpoint;

        double deltaX;
        double deltaY;
        double deltaZ;

};

#endif
