

#ifndef B1DetectorResponse_h
#define B1DetectorResponse_h 1

using namespace std;


#include <string>
#include <fstream>
#include "TROOT.h"
#include "TObject.h"

//! \brief Data structure representing the detector response in a simulated event.
/*!

*/
class B1DetectorResponse : public TObject
{
  public:
  B1DetectorResponse();
  ~B1DetectorResponse();
  void Clear_();
  void random ();
  void Set_energy (Int_t x, Int_t y, Double_t energy);
  Double_t Get_energy (Int_t x, Int_t y);
  void Set_energy_quenching (Int_t x, Int_t y, Double_t energy);
  void Set_photons (Int_t x, Int_t y, Int_t photon);
  void Set_total_energy (Double_t e);
  void Add_fiber_hit ();
  Int_t Get_fiber_hits ();



  // Needed for creation of shared library
  ClassDef(B1DetectorResponse, 1);


  Double_t energy_deposition [30][30];
  Double_t energy_deposition_quenching [30][30];
  Double_t total_energy;
  Int_t  optical_photon_count [30][30];
  Int_t fiber_hits;

  protected:


};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
