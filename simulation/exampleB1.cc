//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: exampleB1.cc 86065 2014-11-07 08:51:15Z gcosmo $
//
/// \file exampleB1.cc
/// \brief Main program of the B1 example

#include "B1DetectorConstruction.hh"
#include "B1ActionInitialization.hh"
#include "DataManager.hh"
#include "B1Config.hh"
#include "B1PhysicsList.hh"

#include <string>

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "FTFP_BERT.hh"
#include "QGSP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

#include <getopt.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

struct sim_config {
    enum SimModel { NOMODEL = 0, CHIPS, QGSP, EM }
        sim_model = NOMODEL;
};

int main(int argc, char** argv)
{
    B1Config* config = new B1Config ();
    sim_config cfg;

    G4UIExecutive* ui = 0;          // UI
    string config_file = "";        // Config file name

    int modus = 0;      // no arguments: modus = 0                  ------>  default
                        // one argument, config mode = 1: modus = 1
                        // one argument, config mode = 2: modus = 2

    int c;
    while(1)
    {
        static struct option long_options[] = {
            { "model", required_argument, 0, 'm' },
            { 0, 0, 0, 0 }
        };

        int option_index = 0;

        c = getopt_long(argc, argv, "m:", long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {
            case 'm':
                {
                    std::string model = optarg;
                    if (model == "chips")
                        cfg.sim_model = sim_config::SimModel::CHIPS;
                    else if (model == "qgsp")
                        cfg.sim_model = sim_config::SimModel::QGSP;
                    else
                    {
                        std::cerr << "Unknown model " << model << std::endl;
                        cfg.sim_model = sim_config::SimModel::NOMODEL;
                    }
                }
                break;
            default:
                break;
        }
    }

    if (optind < argc)
    {
        while (optind < argc)
        {
            config_file  = argv[optind];

            // set the file name of the config name
            config->SetConfigFileName (config_file);

            // load the config file and read it. Return if there is an error
            if (!config->ReadConfigFile())
            {
                printf("Problems reading Config file\n");
                return -1;
            }

            // check for mode defined in config file: 1 = batch mode ; 2 = interactive mode
            if (config->Get_mode() ==  1)
                modus = 1;
            else if (config->Get_mode() ==  2)
            {
                ui = new G4UIExecutive(1, argv);
                modus = 2;
            }
            else if (config->Get_mode() == 3)
                modus = 3;

            ++optind;
            break;
        }
    }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif


  // Set mandatory initialization classes
  //
  // Detector construction
  B1DetectorConstruction* detector_construction = new B1DetectorConstruction(config);
  runManager->SetUserInitialization(detector_construction);

  // DataManager
  DataManager* data_manager = new DataManager();
  data_manager->setSaveFileName (config->Get_filename() );
  data_manager->setSaveTreeName (config->Get_treename() );
  data_manager->setSaveTreeTitle (config->Get_tree_title() );

  // Physics list

    G4VModularPhysicsList* physicsList = nullptr;

    if (cfg.sim_model == sim_config::SimModel::CHIPS)
    {
        std::cout << "Using FTFP model" << std::endl;
        physicsList = new FTFP_BERT;
    }
    else if (cfg.sim_model == sim_config::SimModel::QGSP)
    {
        std::cout << "Using QGSP model" << std::endl;
        physicsList = new QGSP_BERT;
    }
    else
    {
        physicsList = new B1PhysicsList(config);
    }

//   B1PhysicsList* physicsList = new B1PhysicsList(config);
//   G4VModularPhysicsList* physicsList = new  QGSP_BERT;
//   G4VModularPhysicsList* physicsList = new  FTFP_BERT;
  physicsList->SetVerboseLevel(0);
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);

//   B1PhysicsList* physicsList = new B1PhysicsList(config);
// //   G4VModularPhysicsList* physicsList = new  QGSP_BERT;
// //   G4VModularPhysicsList* physicsList = new  FTFP_BERT;
//   physicsList->SetVerboseLevel(0);
//   physicsList->RegisterPhysics(new G4StepLimiterPhysics());
//   runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new B1ActionInitialization(data_manager,config,detector_construction));

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();




  // Process macro or start UI session
  //
  if (modus == 0)                                  // default interactive mode
  {
    // init vis
    string command_init_vis = "/control/execute init_vis.mac";
    UImanager->ApplyCommand(command_init_vis);

    // vis mac
    string command_vis = "/control/execute vis.mac" ;
    UImanager->ApplyCommand(command_vis);

    if (!config->Get_useRootHistoForGun ())
    {
        // Load default GPS mac
        G4String command = "/control/execute run_gps.mac";
        UImanager->ApplyCommand(command);
    }

    ui->SessionStart();
    delete ui;
  }

  else if ((modus == 1) || (modus == 3))                       // batch mode
    {
      printf("\nBatch mode: %d\n", modus);

    // inititalize
    string command_init_vis = "/control/execute " + config->Get_init_vis_file();
    UImanager->ApplyCommand(command_init_vis);

    // If this simulation is executed on the cluster, set the random seeds to job_number, job_number
    if(config->Get_cluster_job())
      {
	// int to string
	int job_number = config->Get_job_number();
	stringstream ss;
	ss << job_number;
	string str = ss.str();
	// create command
	string command_random = "/random/setSeeds " + str  + " " + str ;
	UImanager->ApplyCommand(command_random);
      }

     if (!config->Get_useRootHistoForGun ())
     {
        // load gun mac
        string command_gun_mac = "/control/execute " + config->Get_gun_mac_file();
        UImanager->ApplyCommand(command_gun_mac);
    }

    // start run (only in mode = 1)
    // int to string
    if(modus == 1)
    {
    	int number = config->Get_number_of_events();
    	stringstream ss;
    	ss << number;
    	string str = ss.str();
    	string command_run_beamOn = "/run/beamOn " + str;
    	printf("\nBeamOn command: %s\n", command_run_beamOn.c_str());
    	UImanager->ApplyCommand(command_run_beamOn);
    }
    else if (modus == 3)
    {

    }

    }

  else if (modus == 2)                             // interactive mode
  {
    // init mac
    string command_init_vis = "/control/execute " + config->Get_init_vis_file();
    UImanager->ApplyCommand(command_init_vis);


    // If this simulation is executed on the cluster, set the random seeds to job_number, job_number
    if(config->Get_cluster_job())
      {
	// int to string
	int job_number = config->Get_job_number();
	stringstream ss;
	ss << job_number;
	string str = ss.str();
	// create command
	string command_random = "/random/setSeeds " + str  + " " + str ;
	UImanager->ApplyCommand(command_random);
      }

    // vis mac
    string command_vis = "/control/execute " + config->Get_vis_file();
    UImanager->ApplyCommand(command_vis);

    if (!config->Get_useRootHistoForGun ())
    {
        // load gun mac
        string command_gun_mac = "/control/execute " + config->Get_gun_mac_file();
        UImanager->ApplyCommand(command_gun_mac);
    }

    // start ui session
    ui->SessionStart();
    delete ui;
  }



  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;
  delete config;
}
