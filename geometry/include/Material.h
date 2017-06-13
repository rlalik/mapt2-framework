#ifndef Material_h
#define Material_h 1


#include "globals.hh"
#include <string>
#include <fstream>
#include "G4NistManager.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4SystemOfUnits.hh"
#include <TSpline.h>
#include "TGraph.h"
#include "TFile.h"

using namespace std;

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4PVPlacement;
class G4Material;
class G4NistManager;


//! \brief Represents a material of a detector part.
/*!
  Wraps the Geant4 implementation of a material. For each material we define the
  Geant4 implementation, which makes it usable for the simulation. For the active
  fiber cores we define the optical properties with G4MaterialPropertiesTable. These
  properties are only used by the simulation.

  For the analysis, we define the properties indepent from the G4Material. Density,
  A, Z and radiation length are attributes. CSDA properties are saved in TSpline
  objects. They are evaluated by evaluate functions of this class.

  The material is initialized with the init function, which receives the material
  name as a string a value for the birks coeffizent (double). The init functions
  reads the material name and calls the corresponding build function. The material
  properties are then defined in this build functions.
*/
class Material
{
  public:
  //! \brief Constructor.
  /*!
    Initializes some basic elements and materials to build compounds from it. The
    Geant4 material manager is initialized here.
  */
  Material();

  //! \brief Destructor.
  ~Material ();

  //! \brief Getter function for the G4Material.
  G4Material* getMaterial();

  void buildVacuum();
  void buildAluminium();
  void buildSilicon();
  void buildCopper();
  void buildSteel();
  void buildCarbon();
  void buildTeflon();
  void buildKapton();
  void buildPolystyrene();
  void buildABS();
  void buildPEEK();
  void buildFR4();
  void buildPMMA();
  void buildEpoxySiPM();
  void buildMLI();
  void buildEpoxyEPOTEK();

  //! \brief Initializes the material according to the material name parameter.
  /*!
  The material is initialized with the init function, which receives the material
  name as a string a value for the birks coeffizent (double). The init functions
  reads the material name and calls the corresponding build function. The material
  properties are then defined in this build functions.
  */
  bool Init(string material_, double kB);

  //! \brief Evaluates the TSpline of the stopping power at x-position e (parameter).
  double stoppingPowerEval (double e);

  //! \brief Evaluates the TSpline of the CSDA range at x-position e (parameter).
  double CSDARangeEval (double e);

  //! \brief Evaluates the TSpline of the inverse range at x-position e (parameter).
  double CSDARangeInverseEval (double e);

  //! \brief Evaluates the TSpline of the detour factor at x-position e (parameter).
  double detourEval (double e);

  double getDensity () {return density_;};
  double getZ () {return Z;};
  double getA () {return Z;};
  double getRadiationLength () {return radiationLength;};

  private:
  //! \brief G4Material instance of the material.
  G4Material* material;

  G4Element* elH;
  G4Element* elC;
  G4Element* elN;
  G4Element* elO;
  G4Element* elSi;
  G4Material* matPMMA;

  G4double density;
  double density_;
  int Z;
  int A;
  double radiationLength; // in g/cm^2

  G4double a_mass;

  G4double kBFiber;

  string name;

  G4NistManager* man;

  G4MaterialPropertiesTable* MPT;

  TSpline3* stoppingPower;
  TSpline3* CSDARange;
  TSpline3* CSDARangeInverse;
  TSpline3* detour;

  //! \brief Reads the CSDA tables from the file name submited as parameter.
  TSpline3* readNistTable(const char* filename);

    //! \brief Reads the CSDA tables inversely from the file name submited as parameter.
  TSpline3* readNistTableInverse(const char* filename);


  protected:


};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
