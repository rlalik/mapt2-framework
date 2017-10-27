// STL includes
#include <vector>
#include <time.h>
#include <string.h>
#include <list>
#include <iostream>
#include <chrono>

#include <getopt.h>

// root includes
#include <TCanvas.h>
#include <TLegend.h>
#include <TDatabasePDG.h>
#include <TVector3.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TH1.h>

// MAPT-Analysis framework includes
#include "MGeantTrack.h"
#include "MGeantFibersRaw.h"
#include "MFibersCalSim.h"

#include "MDataManager.h"
#include "MParManager.h"
#include "MDetectorManager.h"

#include "MFibersDetector.h"

using namespace std;

int analysis(const std::string & file, int events = 1000)
{
    TString oname = file;

    if (oname.EndsWith(".root"))
        oname.ReplaceAll(".root", "_ana.root");
    else
        oname.Append("_ana.root");

    // create Data Manager
    MDataManager * dataManager = MDataManager::instance();  // get instance
    dataManager->setSimulation(true);                       // mark that those are simulations
    dataManager->setInputFileName(file);                    // get input file
    dataManager->open();                                    // open the file
    dataManager->setOutputFileName(oname.Data());           // set output file
    dataManager->book();                                    // create output file

    // Initialize parameters. DO IT *before* you initialize detectors.
    // Detector checks whether all required parameters exits!
    MParManager * pm = MParManager::instance();             // get instance
    pm->setParamSource("params.txt");                       // select param file
    pm->parseSource();                                      // parse file into memory

    // Initialize detectors
    // Here you must add all detectors
    MDetectorManager * detm = MDetectorManager::instance();

    // add here each detector you need to include
    MFibersDetector * fd = new MFibersDetector("Fibers");
    fd->setTaskMask(0);             // disable all tasks, e.g. digitizer will override MFibersCalSim
    detm->addDetector(fd);
    // ... more detectors

    // initalzie all detectors
    detm->initTasks();                      // all tasks
    detm->initParameterContainers();        // initalize parameter containes
    detm->initCategories();                 // register all categories

    // initialize tasks
    MTaskManager * tm = MTaskManager::instance();
    tm->initTasks();

    // Crategory must be open to read data or build to store data

    // Open this category if you need access to geant simulations: kine
    MCategory * catGeantTrack = dataManager->openCategory(MCategory::CatGeantTrack);

    // Open this category if you need access to geant simulations: fibers
    MCategory * catGeantFibersRaw = dataManager->openCategory(MCategory::CatGeantFibersRaw);

    // Open this category if you need access to detector cal: fibers
    MCategory * catFibersCalSim = dataManager->openCategory(MCategory::CatFibersCal);

    // build this category if you need access to tracks: fibers
    //MCategory * catFibersTracks = dataManager->buildCategory(MCategory::CatFibersTracks);   // example
    
    int ev_limit = events < dataManager->getEntriesFast() ? events : dataManager->getEntriesFast();
    std::cout << dataManager->getEntriesFast() << " events, analyze " << ev_limit << std::endl;

    size_t tracks_num = 0;
    int secs = 0;
    for (int i=0 ; i < ev_limit; ++i)
    {
        printf("Event = %d\n", i);
        dataManager->getEntry(i);

        //*********************************************************************
        if (!catGeantTrack)
        {
            fprintf(stderr, "No category %s\n", "CatGeantTrack");
        }

        tracks_num = catGeantTrack->getEntries();
        printf("Category %s has %d entries\n", "CatGeantTrack", tracks_num);

        //*********************************************************************
        if (!catGeantFibersRaw)
        {
            fprintf(stderr, "No category %s\n", "CatGeantFibersRaw");
        }

        tracks_num = catGeantFibersRaw->getEntries();
        printf("Category %s has %d entries\n", "CatGeantFibersRaw", tracks_num);

        //*********************************************************************
        if (!catFibersCalSim)
        {
            printf("No category %s\n", "CatFibersCal");
        }

        tracks_num = catFibersCalSim->getEntries();
        fprintf(stderr, "Category %s has %d entries\n", "CatFibersCal", tracks_num);
    }

    return 0;
}

int main(int argc,char** argv)
{
    int events = 10000;
    int c;
    while(1)
    {
        static struct option long_options[] = {
            { "events", required_argument, 0, 'e' },
            { 0, 0, 0, 0 }
        };

        int option_index = 0;

        c = getopt_long(argc, argv, "e:", long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {
            case 'e':
                events = atoi(optarg);
                break;
            default:
                break;
        }
    }

    std:vector< std::pair<std::string, int> > ana_status;
    while (optind < argc)
    {
        std::cout << "Analyze " << argv[optind] << std::endl;
        int status = analysis(argv[optind], events);
        std::string f = argv[optind];
        ana_status.push_back({f, status});
        ++optind;
    }

    for (int i = 0; i < ana_status.size(); ++i)
    {
        std::cout << "Analysis for " << ana_status[i].first << " with status " << ana_status[i].second << std::endl;
//         std::cout << "Output file is " << oname.Data() << std::endl;
    }

    return 0;
}
