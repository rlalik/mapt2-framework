#ifndef UserGeant4Geometry_h
#define UserGeant4Geometry_h

// stl
#include <vector>
#include <string>

// Geant4
#include <G4LogicalVolume.hh>
#include <G4ThreeVector.hh>
#include <G4Navigator.hh>
#include <G4VPhysicalVolume.hh>
#include <G4LogicalVolume.hh>
#include <G4Box.hh>
#include <G4Material.hh>
#include <G4TouchableHistory.hh>
#include <G4SystemOfUnits.hh>
#include <G4PhysicalConstants.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>

// cadmesh
#include <CADMesh.hh>

// root
#include <TVector3.h>

// geometry shared library
#include "Material.h"
#include "AbsPart.h"
#include "CADPart.h"
#include "CADFiber.h"
#include "GeometryReadIn.h"


class GeometryReadIn;



//! \brief Defines the detector geometry on Geant4 basis using a geometry file.
/*!
  Defines the detector geometry on Geant4 basis using a geometry file. Key class
  of the geometry repersentation. The user provides a file path to the geometry
  text file in the constructor and calls the construct function. The geometry is
  set up in the construct function according to the parts specified in the geometry
  text file.

  UserGeant4Geometry provides all needed functions to access the geometry wrapping
  the G4Navigator functionalities.
*/
class UserGeant4Geometry {
    public:

    /*! \brief Constructor
    /*!
     Initializes the geometry reader (GeometryReadIn).
    */
    UserGeant4Geometry(string filePath, bool drawable_ = false);

    //! \brief Destructor. Does nothing.
    ~UserGeant4Geometry() {;};

    //! \brief Constructs the geometry accodring to the geometry text file.
    /*!
      Creates a world volume and fills it with vaccum. Calls the read function of
      the geometry reader. Places the detector parts in the world. Initializes the
      G4Navigator.
    */
    void construct ();

    //! \brief Adds a part to the part list.
    void addPart(AbsPart* part_);

    //! \brief Returns the CADFiber indentified by its position (x,y) in the Hits30x30 array.
    CADFiber* getFiber(int x, int y);

    //! \brief Returns the detector part identified by its G4LogicalVolume.
    AbsPart* getPart (G4LogicalVolume* vol);

    //! \brief Returns the detector part identified by its volume index.
    AbsPart* getPart (int volumeIndex_);

    //! \brief Returns the world volume.
    G4VPhysicalVolume* getWorld () {return world;};

    string getGeometryFilePath () {return geometryFilePath;};
    bool getDrawable () {return drawable;};

    //! \brief Returns the detector part identified by its volume index.
    AbsPart* getCurrentPart (int volumeIndex_);

    //! \brief Returns the G4LogicalVolume which surounds the position given as parameter.
    G4LogicalVolume* getCurrentPart (TVector3 pos);

    //! \brief Finds the next volume, identfies it, and calculates the intersection points.
    /*!
      Key function to find the next step through a volume. Starting from pIn
      the function tries to find the next volume in direction dir.

      The function returns a 0 if no further volume is found in that
      direction (-> left world).

      If the next volume is found the function returns a 1. newPIn is the new entry
      point, newPOut is the new exit point, and volumeIndex_ is the volume index
      of the traversed volume.

      The function return -1 if an error occurs during calculation.
    */
    int getNextStep (TVector3 pIn, TVector3 dir, TVector3 &newPIn, TVector3 &newPOut, int &volumeIndex_);

    //! \brief Finds the next intersection point by wrapping the G4Navigator functions.
    bool findNextIntersectionPoint (TVector3 startPoint, TVector3 direction, TVector3 &intersection);


    void setSafety (double s) {safety = s;};
    double getSafety () {return safety;};

    //! \brief Sets the maximal step size in the fiber volumes (needed in simulation only).
    void setMaxStepInFiber (double maxStep);

    private:
    //! \brief Defines if the geometry is drawable.
    /*!
    We can use the CAD information to draw the part. If drawable is true, we
    extract the triangles and vertices from the CAD model and save them in
    each part. This operation is time consuming and not needed in many
    applications of the framework. Therefore, the user
    can switch this option on or off with the drawable variable.
    */
    bool drawable;

    //! \brief Path to geometry text file.
    string geometryFilePath;

    //! \brief World volume.
    G4VPhysicalVolume* world;

    //! \brief List of all detector parts in the geometry.
    vector<AbsPart*> parts;

    //! \brief Geoemtry reader.
    GeometryReadIn* reader;

    //! \brief G4Navigator object.
    G4Navigator* nav;

    //! \brief A safety parameter for geometry calculation.
    double safety;
};

#endif
