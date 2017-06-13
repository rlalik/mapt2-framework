#ifndef AbsPartCGAL_h
#define AbsPartCGAL_h

// stl
#include <vector>

// Geant4

// root
#include <TVector3.h>

// geometry shared library
#include "Material.h"

//! \brief Defines an abstract detector part for the geometry representation with CGAL.
/*!
  Defines an abstract detector part in more detail.
*/
class AbsPartCGAL {
public:
    //! \brief Constructor.
    /*!
      Sets the default values.
    */
    AbsPartCGAL (bool drawable_);

    //! \brief Virtual destructor.
    virtual ~AbsPartCGAL () {;};

    //! \brief Returns drawable.
    bool getDrawable () {return drawable;};

    //! \brief Returns the volume index of the part.
    int getVolumeIndex () {return volumeIndex;};

    //! \brief Sets the volume index.
    void setVolumeIndex (int i) {volumeIndex = i;};

    //! \brief Returns the material of the part.
    Material* getMaterial() {return material;};

protected:
    //! \brief Defines if the part is drawable.
    /*!
      We can use the CAD information to draw the part. If drawable is true, we
      extract the triangles and vertices from the CAD model and save them in the
      member variable triangles and vertices. This operation is time consuming
      and not needed in many applications of the framework. Therefore, the user
      can switch this option on or off with the drawable variable.

      This option is currently not available for the geometry representation
      on CGAL basis.
    */
    bool drawable;

    //! \brief The material object of this part.
    Material* material;

    //! \brief The volume index of the part.
    /*!
      The volume index identifies a part in the geometry.
    */
    int volumeIndex;

};

#endif
