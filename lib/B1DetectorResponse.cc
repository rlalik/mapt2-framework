#include "B1DetectorResponse.hh"

// Needed for Creation of shared libs
ClassImp(B1DetectorResponse);

B1DetectorResponse::B1DetectorResponse()
{ 
}



B1DetectorResponse::~B1DetectorResponse()
{
}

void B1DetectorResponse::Clear_()
{
  for (int i=0;i<30;i++)
    {
      for (int j=0;j<30;j++)
	{
	  energy_deposition[i][j]= 0;
	  energy_deposition_quenching[i][j]= 0;
	  optical_photon_count[i][j] = 0;
	}
    }

  total_energy = 0;
  fiber_hits = 0;

}


void B1DetectorResponse::random()
{
  for (int i=0;i<30;i++)
    {
      for (int j=0;j<30;j++)
	{
	  energy_deposition[i][j]= j*j;
	  energy_deposition_quenching[i][j]= i*i;
	  optical_photon_count[i][j] = j*i;
	}
    }

  total_energy = 0;
}


void B1DetectorResponse::Set_energy (Int_t x, Int_t y, Double_t energy)
{
  energy_deposition[x][y] += energy;
}

void B1DetectorResponse::Set_energy_quenching (Int_t x, Int_t y, Double_t energy)
{
  energy_deposition_quenching[x][y] += energy;
}

void B1DetectorResponse::Set_photons (Int_t x, Int_t y, Int_t photon)
{
  optical_photon_count[x][y] += photon;
}

void B1DetectorResponse::Set_total_energy (Double_t e)
{
  total_energy += e;
}

void B1DetectorResponse::Add_fiber_hit ()
{
  fiber_hits++;
}

Int_t B1DetectorResponse::Get_fiber_hits ()
{
  return fiber_hits;
}

Double_t B1DetectorResponse::Get_energy (Int_t x, Int_t y)
{
  return energy_deposition[x][y];
}
