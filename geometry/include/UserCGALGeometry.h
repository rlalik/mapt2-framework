#ifndef UserCGALGeometry_h
#define UserCGALGeometry_h


// STL includes
#include <string>

// geant4 includes


// cadmes include
#include "CADMesh.hh"

// MAPT-Analysis framework includes
#include "AbsPartCGAL.h"
#include "CADPartCGAL.h"
#include "CADFiberCGAL.h"
#include "GeometryReadInCGAL.h"
#include "trianglemesh.h"

class GeometryReadInCGAL;

//! \brief Defines the detector geometry on CGAL basis using a geometry file.
/*!
  Defines the detector geometry on CGAL basis using a geometry file. Key class
  of the geometry repersentation. The user provides a file path to the geometry
  text file in the constructor and calls the construct function. The geometry is
  set up in the construct function according to the parts specified in the geometry
  text file. The material definition is still done on a Geant4 basis, but navigation
  is completely seperated from Geant4.

  UserCGAL4Geometry provides all needed functions to access the geometry. The
  geometry information is contained in a TTriangleMesh object, which is the
  interface to the AABB tree and the other CGAL functionalities.
*/
class UserCGALGeometry {
public:
    /*! \brief Constructor
    /*!
     Initializes the geometry reader (GeometryReadInCGAL).
    */
    UserCGALGeometry(string filePath, bool drawable_);

    //! \brief Destructor. Does nothing.
    ~UserCGALGeometry() {;};

    //! \brief Constructs the geometry accodring to the geometry text file.
    /*!
      Calls the read function of the geometry reader. Initializes the TTriangleMesh.
    */
    void construct ();

    //! \brief Adds a part to the part list and reads in the CAD information to TTriangleMesh.
    void addPart(AbsPartCGAL* part_);

    //! \brief Finds the next volume, identfies it, and calculates the intersection points.
    /*!
      Calls TTriangleMesh::nextIntersection2().
    */
    int getNextStep (TVector3 startPoint, TVector3 direction,TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex);

    //! \brief Returns the CADFiberCGAL indentified by its position (x,y) in the Hits30x30 array.
    CADFiberCGAL* getFiber(int x, int y);


    string getGeometryFilePath () {return geometryFilePath;};
    bool getDrawable () {return drawable;};

    //! \brief Returns the detector part identified by its volume index.
    AbsPartCGAL* getCurrentPart (int index);

private:
    //! \brief Presentation of the geometry.
    TTriangleMesh* mesh;

    //! \brief Defines if the geometry is drawable.
    /*!
    We can use the CAD information to draw the part. If drawable is true, we
    extract the triangles and vertices from the CAD model and save them in
    each part. This operation is time consuming and not needed in many
    applications of the framework. Therefore, the user
    can switch this option on or off with the drawable variable.

    This functionalities are not implemented in the CGAL based geometry
    representation.
    */
    bool drawable;

    double safety;
    string geometryFilePath;

    //! \brief List of all detector parts in the geometry.
    vector<AbsPartCGAL*> parts;

    //! \brief Geoemtry reader.
    GeometryReadInCGAL* reader;

};

#endif
