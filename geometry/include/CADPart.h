#ifndef CADPart_h
#define CADPart_h

// stl
#include <vector>
#include <string>
#include <fstream>

// Geant4
#include <G4LogicalVolume.hh>
#include <G4TessellatedSolid.hh>

// root
#include <TVector3.h>

// cadmesh
#include "CADMesh.hh"

// geometry shared library
#include "Material.h"
#include "AbsPart.h"

//! \brief Defines a CAD part for the geometry representation with Geant4.
/*!
  Defines a CAD part. Derived from AbsPart. Defines an init() function to
  initialize the part.
*/
class CADPart : public AbsPart {
public:
    //! \brief Constructor. Does nothing.
    CADPart (bool drawable_);

    //! \brief Destructor. Does nothing.
    ~CADPart () {;};

    //! \brief Reads in the CAD file (STL format) and assigns a material
    /*!
      This function assigns a material to the part according to the string parameter
      it receives. The path_ parameter is the path to the CAD file, which describes
      the geometry of the path. The geometry of the path is loaded with the cadmesh
      library.
    */
    void Init (string path_, string material_, string color_);

    //! \brief Returns the path to the CAD file.
    string getPath () {return path;};

protected:
    //! \brief Path to the CAD file (STL format).
    string path;
    //! \brief Material name as string.
    string materialName;
    //! \brief A color attribute for drawing the part (currently not used).
    string color;

};

#endif
