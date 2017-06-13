

#include "B1Config.hh"
#include <string>


B1Config::B1Config ()
{
  config_file = "";
  init_vis_file= "";
  vis_file = "";
  gun_mac_file = "";
  geometry_file = "";
  tree_title = "";
  treename = "";
  filename = "";

  optical_process = true;
  step_length_in_fiber = 100;

  number_of_events = 0;
  cluster_job = false;
  job_number = 1;
  kB = 0.13;
  maxStep = 1;
  electronCutValue = 1.0;
  useRootHistoForGun = false;
  rootFile = "";
  particleName = "proton";

  // standard mode is batch mode
  mode = 1;
}

B1Config::~B1Config()
{

}


bool B1Config::ReadConfigFile()
{
  if (config_file == "")
    {
      printf("Config File not found");
      return false;
    }

  // Check if file is there and open file
  data.open(config_file.c_str() ,std::fstream::in);

  if (data.fail())
    {
      printf("Config File %s not found", config_file.c_str());
      return false;
    }


  string line = "";

  // Read file by line
  while (!data.eof())
    {
       getline(data,line);
       readline(line);
    }

  // Close stream
  data.close();

  PrintConfig();

  return true;
}


void B1Config::readline (string l)
{
  string line = l;
  string s = "";

  if (line[0] == '#')
    {
      // Comment. Do nothing.
    }

  // Init Visualisation file
  else if (line.find("InitVis file") != string::npos )
    {
      init_vis_file = GetParameter (line);
    }

  // Visualisation file
  else if (line.find("Visualisation file") != string::npos)
    {
      vis_file = GetParameter (line);
    }

  // Gun mac file
  else if (line.find("Gun mac file") != string::npos)
    {
      gun_mac_file = GetParameter (line);
    }

  // Geometry file
  else if (line.find("Geometry file") != string::npos)
    {
      geometry_file = GetParameter (line);
    }

  // mode
  else if (line.find("Mode") != string::npos)
    {
      string mode_s = GetParameter (line);

      std::stringstream convert(mode_s); // stringstream used for the conversion initialized with the contents of Text

      if ( !(convert >> mode) ) //give the value to mode using the characters in the string
	mode = 0; //if that fails set mode to 0
    }

  // number of Events
  else if (line.find("Number of Events") != string::npos)
    {
      string number_s = GetParameter (line);

      std::stringstream convert(number_s); // stringstream used for the conversion initialized with the contents of Text

      if ( !(convert >> number_of_events) ) //give the value to mode using the characters in the string
	number_of_events = 0; //if that fails set mode to 0
    }

  // optical processes
  else if (line.find("Optical processes") != string::npos)
    {
      string para  = GetParameter (line);

      if (para == "true")
	{
	  optical_process = true;
	}
      else
	{
	  optical_process = false;
	}
    }

  // root filename
  else if (line.find("Root filename") != string::npos)
    {
      filename = GetParameter (line);
    }

  // root tree title
  else if (line.find("Root tree title") != string::npos)
    {
      tree_title = GetParameter (line);
    }

  // root treename
  else if (line.find("Root tree name") != string::npos)
    {
      treename = GetParameter (line);
    }

  // cluster job
  else if (line.find("Cluster job") != string::npos)
    {
          string para  = GetParameter (line);

          if (para == "true")
    	{
    	  cluster_job = true;
    	}
          else
    	{
    	  cluster_job = false;
    	}
    }

  // job number
  else if (line.find("Job number") != string::npos)
    {
      string job_s = GetParameter (line);

      std::stringstream convert(job_s); // stringstream used for the conversion initialized with the contents of Text

      if ( !(convert >> job_number) ) //give the value to mode using the characters in the string
	job_number = 1; //if that fails set job_number to 1
    }

  // kB
  else if (line.find("Birks coefficient") != string::npos)
    {
      string kB_s = GetParameter (line);

      std::stringstream convert(kB_s); // stringstream used for the conversion initialized with the contents of Text

      if ( !(convert >> kB) ) //give the value to mode using the characters in the string
	kB = 1 ; //if that fails set job_number to 1

    }

  // maxStep
  else if (line.find("Maximal Step in Fiber") != string::npos)
    {
      string maxStep_s = GetParameter (line);

      std::stringstream convert(maxStep_s); // stringstream used for the conversion initialized with the contents of Text

      if ( !(convert >> maxStep) ) //give the value to mode using the characters in the string
	maxStep = 1 ; //if that fails set job_number to 1

    }

    // electronCutValue
    else if (line.find("Electron Cut Value") != string::npos)
    {
        string electronCutValue_s = GetParameter (line);

        std::stringstream convert(electronCutValue_s); // stringstream used for the conversion initialized with the contents of Text

        if ( !(convert >> electronCutValue) ) //give the value to mode using the characters in the string
    	   electronCutValue = 1 ; //if that fails set job_number to 1
    }

    // use histogram for gun
    else if (line.find("Root Histo for gun") != string::npos)
      {
            string para  = GetParameter (line);

            if (para == "true")
          {
            useRootHistoForGun = true;
          }
            else
          {
            useRootHistoForGun = false;
          }
      }

    // root gun histo
      else if (line.find("Path to Gun Histo") != string::npos)
        {
          rootFile = GetParameter (line);
        }

    // root treename
    else if (line.find("Particle type") != string::npos)
    {
        particleName = GetParameter (line);
    }
}



void B1Config::PrintConfig ()
{
  printf ("\nConfig: \n");
  printf("Config File: %s\n", config_file.c_str());
  printf("Init Visualisation: %s\n", init_vis_file.c_str());
  printf("Visualisation: %s\n", vis_file.c_str());
  printf("Gun mac file: %s\n", gun_mac_file.c_str());
  printf("Geometry file: %s\n", geometry_file.c_str());
  printf("Mode: %u\n", mode);
  printf("Number of Events: %u\n", number_of_events);
  printf("Optical processes: %d\n", optical_process);
  printf("Root filename: %s\n", filename.c_str());
  printf("Root tree title: %s\n", tree_title.c_str());
  printf("Root tree name: %s\n", treename.c_str());
  printf("Cluster job: %d\n", cluster_job);
  printf("Job number: %u\n", job_number);
  printf("kB: %f\n", kB);
  printf("Max Step in Fiber: %f\n", maxStep);
  printf("Electron Cut Value: %f\n", electronCutValue);
  printf("Root Histo for gun: %d\n", useRootHistoForGun);
  printf("Root File Histo Gun: %s\n", rootFile.c_str());
  printf("Particle Type: %s\n", particleName.c_str());
  printf("\n\n");

}



string B1Config::GetParameter (string l)
{
  string line = l;
  string parameter = "";

  int start = line.find_first_of("\"");
  int end = line.find_last_of("\"");

  parameter  = line.substr(start+1,end-start-1);
  return parameter;
}



string B1Config::Get_init_vis_file ()
{
  return init_vis_file;
}


string B1Config::Get_vis_file ()
{
  return vis_file;
}


string B1Config::Get_gun_mac_file ()
{
  return gun_mac_file;
}


string B1Config::Get_geometry_file ()
{
  return geometry_file;
}

void B1Config::SetConfigFileName (string file)
{
  config_file = file;
}

int B1Config::Get_mode ()
{
  return mode;
}

int B1Config::Get_number_of_events ()
{
  return number_of_events;
}

bool B1Config::Get_optical_processes ()
{
  return optical_process;
}

string B1Config::Get_tree_title ()
{
  return tree_title;
}

string B1Config::Get_filename ()
{
  return filename;
}

string B1Config::Get_treename ()
{
  return treename;
}

bool B1Config::Get_cluster_job ()
{
  return cluster_job;
}

int B1Config::Get_job_number ()
{
  return job_number;
}

G4double B1Config::Get_kB ()
{
  return kB;
}

G4double B1Config::Get_maxStep ()
{
  return maxStep;
}


G4double B1Config::Get_electronCutValue ()
{
  return electronCutValue;
}

bool B1Config::Get_useRootHistoForGun ()
{
  return useRootHistoForGun;
}

string B1Config::Get_rootFile ()
{
  return rootFile;
}

string B1Config::Get_particleName ()
{
  return particleName;
}
