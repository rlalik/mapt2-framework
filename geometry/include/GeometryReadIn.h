#ifndef GeometryReadIn_h
#define GeometryReadIn_h 1

// stl
#include <string>
#include <fstream>

// Geant4
#include <globals.hh>
#include <G4LogicalVolume.hh>

// root
#include <TVector3.h>

// geometry shared library
#include "UserGeant4Geometry.h"
#include "CADFiber.h"

class CADFiber;
class UserGeant4Geometry;


//! \brief Reads the geometry text file, creates the detector parts defined in the geometry text file, and adds them to the geometry (UserGeant4Geometry).
/*!

*/
class GeometryReadIn
{
  public:
    //! \brief Constructor. Receives a pointer to the geometry and a file path to the geometry text file.
    GeometryReadIn (UserGeant4Geometry* geo, string filename_);

    //! \brief Destructor. Does nothing.
    ~GeometryReadIn() {;};

    //! \brief Loads and reads the geometry text file line by line.
    /*!
      Loads the geometry text file. Iterates over the number of lines in the file.
      Extracts each line to a string and submits this string to the readline function.
    */
    void read ();

  private:
      //! \brief Reads and interpretes a line from the geometry text file.
      /*!
        Extracts the commands from the gemetry text files. Calls the loadPart
        functions if it reads a new part.
      */
    void readline (string l);

    //! \brief Loads a detector part and adds it to the geometry.
    /*!

    */
    void loadPart (string path_, string material_, string detector_, string color_);

    //! \brief Loads several detector part and adds them to the geometry.
    /*!

    */
    void loadPart (string path_, string material_, string detector_, string color_, string start_, string end_);

    //! \brief Checks if the geometry file exists.
    inline bool fileExist (const std::string& name) {
        ifstream f(name.c_str());
        return f.good();
    }

    //! \brief Pointer to geometry.
    UserGeant4Geometry* geometry;

    //! \brief Streams the data file.
    fstream datei;

    //! \brief File path to geometry text file.
    string filename;

    //! \brief If true, the reader is in the repeat section of the geometry text file and loads several parts for each line.
    bool repeat;

};


#endif
