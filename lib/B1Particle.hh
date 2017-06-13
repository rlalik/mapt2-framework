#ifndef B1Particle_h
#define B1Particle_h

using namespace std;

//#include "globals.h"
#include <string>
#include <fstream>
#include "TROOT.h"
#include "TRandom2.h"
#include "TVector3.h"

class TObject;

//! \brief Data structure representing a charged particle.
/*!
Represents a charged particle in the Geant4 simulation. Needed to save the MC truth.
*/
class B1Particle : public TObject
{
public:
    B1Particle();
    ~B1Particle();

    void Clear_();
    void random();                                      // creates a particle with random values for testing
    double get_random_number();                         // returns a random number between 0 and 1 (without 0 and 1)
    void Add_Process (string name);
    void Add_Daughter_ID (int ID);

    TVector3 Get_start_position();
    void Set_start_position(TVector3 p);

    TVector3 Get_end_position();
    void Set_end_position(TVector3 p);

    TVector3 Get_start_direction();
    void Set_start_direction(TVector3 p);

    TVector3 Get_end_direction();
    void Set_end_direction(TVector3 p);

    bool Get_scattering();
    void Set_scattering(bool b);

    std::vector<string> Get_processes();
    void Set_processes(std::vector<string> v);

    int Get_geant4_number();
    void Set_geant4_number(int i);

    bool Get_stop_in_detector();
    void Set_stop_in_detector(bool b);

    std::vector<int> Get_secondaries_ID();
    void Set_secondaries_ID(std::vector<int> v);

    int Get_particle_ID();
    void Set_particle_ID(int i);

    string Get_generation_process();
    void Set_generation_process(string i);

    double Get_start_energy();
    void Set_start_energy(double i);

    double Get_end_energy();
    void Set_end_energy(double i);

    void print() const;
    bool isPim() const { return geant4_number == -211; }
    bool isPip() const { return geant4_number == 211; }
    bool isPiz() const { return geant4_number == 111; }
    bool isP() const { return geant4_number == 2212; }
    bool isaP() const { return geant4_number == -2212; }

    // Needed for creation of shared library
    ClassDef(B1Particle, 1);

private:
    TVector3 start_position;
    TVector3 end_position;
    TVector3 start_direction;
    TVector3 end_direction;
    bool scattering;
    std::vector<string> processes;
    int geant4_number;
    bool stop_in_detector;
    std::vector<int> secondaries_ID;
    int particle_ID;
    string generation_process;
    double start_energy;
    double end_energy;

    TRandom2 rand_gen;

protected:

};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
