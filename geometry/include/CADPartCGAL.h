#ifndef CADPartCGAL_h
#define CADPartCGAL_h

// stl
#include <vector>
#include <string>
#include <fstream>

// Geant4

// root
#include <TVector3.h>

// cadmesh

// geometry shared library
#include "Material.h"
#include "AbsPartCGAL.h"

//! \brief Defines a CAD part for the geometry representation with CGAL.
/*!
  Defines a CAD part. Derived from AbsPartCGAL. Defines an init() function to
  initialize the part.
*/
class CADPartCGAL : public AbsPartCGAL {
public:
    //! \brief Constructor. Does nothing.
    CADPartCGAL (bool drawable_);

    //! \brief Destructor. Does nothing.
    ~CADPartCGAL () {;};

    //! \brief Assigns a material and saves the CAD file path.
    /*!
      This function assigns a material to the part according to the string parameter
      it receives. The path_ parameter is the path to the CAD file and saved as attribute.
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
