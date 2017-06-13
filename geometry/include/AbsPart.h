#ifndef AbsPart_h
#define AbsPart_h

// stl
#include <vector>

// Geant4
#include <G4LogicalVolume.hh>

// root
#include <TVector3.h>

// geometry shared library
#include "Material.h"

//! \brief Defines an abstract detector part for the geometry representation with Geant4.
/*!
  Defines an abstract detector part.
*/
class AbsPart {

public:
    //! \brief Constructor.
    /*!
      Sets the default values.
    */
    AbsPart (bool drawable_);


    //! \brief Virtual destructor.
    virtual ~AbsPart () {;};

    //! \brief Returns the logical volume of the part.
    G4LogicalVolume* getLogical () {return logical;};

    //! \brief Returns the the number of triangel.
    int getNumberTriangle () {return numberTriangles;};

    //! \brief Returns the number of vertices.
    int getNumberVertices () {return numberVertices;};

    //! \brief Returns the vector of vertices.
    std::vector<TVector3> getVertices () {return vertices;};

    //! \brief Returns the triangles.
    std::vector<std::vector<int> > getTriangles () {return triangles;};

    //! \brief Returns true if the part is drawable.
    bool getDrawable () {return drawable;};

    //! \brief Returns the volume index of the part.
    int getVolumeIndex () {return volumeIndex;};

    //! \brief Sets the volume index.
    void setVolumeIndex (int i) {volumeIndex = i;};

protected:
    //! \brief Defines if the part is drawable.
    /*!
      We can use the CAD information to draw the part. If drawable is true, we
      extract the triangles and vertices from the CAD model and save them in the
      member variable triangles and vertices. This operation is time consuming
      and not needed in many applications of the framework. Therefore, the user
      can switch this option on or off with the drawable variable.
    */
    bool drawable;

    //! \brief The G4LogicalVolume of this part.
    G4LogicalVolume* logical;

    //! \brief The material object of this part.
    Material* material;

    //! \brief Vertices.
    std::vector<TVector3> vertices;

    //! \brief Triangles.
    std::vector<std::vector<int> > triangles;

    //! \brief Number of triangles.
    int numberTriangles;

    //! \brief Number of vertices.
    int numberVertices;

    //! \brief The volume index of the part.
    /*!
      The volume index identifies a part in the geometry.
    */
    int volumeIndex;

};

#endif
