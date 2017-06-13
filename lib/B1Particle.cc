#include "B1Particle.hh"

// Needed for Creation of shared libs
ClassImp(B1Particle);

//
// Constructor
//
//
B1Particle::B1Particle()
{
  Clear_();
}
//
//

B1Particle::~B1Particle()
{

}

void B1Particle::Clear_()
{

  TVector3 p (0,0,0);

  start_position                       = p;
  end_position                         = p;
  start_direction                      = p;
  end_direction                        = p;
  scattering                           = false;
  processes.clear();
  geant4_number                        = 0;
  stop_in_detector                     = false;
  secondaries_ID.clear();
  particle_ID                          = 0;
  generation_process                   = "";

}

void B1Particle::random()
{

  double x = get_random_number()*10;
  double y = get_random_number()*10;
  double z = get_random_number()*10;

  TVector3 p (x,y,z);

  start_position                       = p;
  end_position                         = p;
  start_direction                      = p;
  end_direction                        = p;
  scattering                           = false;
  geant4_number                        = 1;
  stop_in_detector                     = false;
  secondaries_ID.push_back((int) get_random_number()*100);
  particle_ID                          = (int)get_random_number()*100;
}

double B1Particle::get_random_number()
{
  return rand_gen.Rndm();
}


TVector3 B1Particle::Get_start_position ()
{
  return start_position;
}

void B1Particle::Set_start_position (TVector3 p)
{
  start_position = p;
}


TVector3 B1Particle::Get_end_position ()
{
  return end_position;
}

void B1Particle::Set_end_position (TVector3 p)
{
  end_position = p;
}

TVector3 B1Particle::Get_start_direction ()
{
  return start_direction;
}

void B1Particle::Set_start_direction (TVector3 p)
{
  start_direction = p;
}

TVector3 B1Particle::Get_end_direction ()
{
  return end_direction;
}

void B1Particle::Set_end_direction (TVector3 p)
{
  end_direction = p;
}

bool B1Particle::Get_scattering ()
{
  return scattering;
}

void B1Particle::Set_scattering (bool b)
{
  scattering = b;
}

std::vector<string> B1Particle::Get_processes ()
{
  return processes;
}

void B1Particle::Set_processes (std::vector<string> v)
{
  processes = v;
}

int B1Particle::Get_geant4_number ()
{
  return geant4_number;
}

void B1Particle::Set_geant4_number (int i)
{
  geant4_number = i;
}

bool B1Particle::Get_stop_in_detector ()
{
  return stop_in_detector;
}

void B1Particle::Set_stop_in_detector (bool b)
{
  stop_in_detector = b;
}

std::vector<int> B1Particle::Get_secondaries_ID ()
{
  return secondaries_ID;
}

void B1Particle::Set_secondaries_ID (std::vector<int> v)
{
  secondaries_ID = v;
}

int B1Particle::Get_particle_ID ()
{
  return particle_ID;
}

void B1Particle::Set_particle_ID (int i)
{
  particle_ID = i;
}

string B1Particle::Get_generation_process ()
{
  return generation_process;
}

void B1Particle::Set_generation_process (string i)
{
  generation_process = i;
}


void B1Particle::Add_Process(string name)
{
  processes.push_back(name);
}


void B1Particle::Add_Daughter_ID(int ID)
{
  secondaries_ID.push_back(ID);
}


double B1Particle::Get_start_energy ()
{
  return start_energy;
}

void B1Particle::Set_start_energy (double i)
{
  start_energy = i;
}


double B1Particle::Get_end_energy ()
{
  return end_energy;
}

void B1Particle::Set_end_energy (double i)
{
  end_energy = i;
}

void B1Particle::print() const
{
    printf("##### particle #####\n");
    printf("  pos sta=(%f,%f,%f)  sto=(%f,%f,%f)\n", start_position.X(), start_position.Y(), start_position.Z(),
           end_position.X(), end_position.Y(), end_position.Z());
    printf("  dir sta=(%f,%f,%f)  sto=(%f,%f,%f)\n", start_direction.X(), start_direction.Y(), start_direction.Z(),
           end_direction.X(), end_direction.Y(), end_direction.Z());

    printf("  scat=%d  process=", scattering);
    for (int i = 0; i < processes.size(); ++i)
        printf("%s,", processes[i].c_str());
    printf("\n");
    printf("  PID=%d  stop in det=%d\n", geant4_number, stop_in_detector);
    printf("  num of sec=%d\n", secondaries_ID.size());
//   std::vector<int> secondaries_ID;
//   int particle_ID;
//   string generation_process;
//   double start_energy;
//   double end_energy;

//   TRandom2 rand_gen;
}
