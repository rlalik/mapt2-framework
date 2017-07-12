

#ifndef B1Config_h
#define B1Config_h 1

using namespace std;


#include <string>
#include <fstream>
#include "TROOT.h"
#include "TObject.h"
#include <sstream>
#include "globals.hh"

class B1Config
{
  public:
  B1Config();
  ~B1Config();

  void SetConfigFileName (string file);
  bool ReadConfigFile ();

  string Get_init_vis_file ();
  string Get_vis_file ();
  string Get_gun_mac_file ();
  string Get_geometry_file ();
  int Get_mode ();
  int Get_number_of_events ();
  bool Get_optical_processes ();
  string Get_tree_title ();
  string Get_filename ();
  string Get_treename ();
  bool Get_cluster_job ();                                   // The current simulation is executed on the cluster --> needed to set different seeds
  int Get_job_number ();                                     // Number of current job at the cluster (only needed, if cluster_job = true)
  G4double Get_kB();
  G4double Get_maxStep ();
  G4double Get_electronCutValue ();
  bool Get_useRootHistoForGun ();
  string Get_rootFile ();
  string Get_particleName ();

  void readline (string l);
  string GetParameter (string l);

  void PrintConfig ();


  private:

  // files
  string config_file;
  string init_vis_file;
  string vis_file;
  string gun_mac_file;
  string geometry_file;
  // parameters
  bool optical_process;
  double step_length_in_fiber;
  string tree_title;
  string filename;
  string treename;
  G4double kB;
  G4double maxStep;
  G4double electronCutValue;
  bool useRootHistoForGun;
  string rootFile;
  string particleName;

  int mode;                          // batch mode = 1 / interactive mode = 2 / batch mode no beamOn = 3
  int number_of_events;
  bool cluster_job;
  int job_number;

  fstream data;


  protected:


};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
