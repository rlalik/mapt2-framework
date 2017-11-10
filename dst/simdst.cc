// STL includes
#include <vector>
#include <time.h>
#include <string.h>
#include <list>
#include <iostream>
#include <chrono>

#include <getopt.h>

// root includes
#include <TDatabasePDG.h>
#include <TVector3.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TH1.h>

// MAPT-Analysis framework includes
#include "MGeantTrack.h"
#include "MGeantFibersRaw.h"

#include "MMAPTManager.h"
#include "MDetectorManager.h"
#include "MTaskManager.h"
#include "MParManager.h"

#include "MFibersStackDetector.h"

using namespace std;

int simdst(const std::string & file, int events = 1000)
{
    TString oname = file;

    if (oname.EndsWith(".root"))
        oname.ReplaceAll(".root", "_digi.root");
    else
        oname.Append("_digi.root");

    // Init data manager
    MMAPTManager * dataManager = MMAPTManager::instance();
    dataManager->setSimulation(true);

    // input files
    dataManager->setInputFileName(file);
    dataManager->open();

    // output files
    dataManager->setOutputFileName(oname.Data());
    dataManager->book();

    // how many events to proceed
    int ev_limit = events < dataManager->getEntriesFast() ? events : dataManager->getEntriesFast();
    std::cout << dataManager->getEntriesFast() << " events, analyze " << ev_limit << std::endl;

    dataManager->openCategory(MCategory::CatGeantTrack, true);

    // initialize parameters
    MParManager * pm = MParManager::instance();
    pm->setParamSource("params.txt");
    pm->parseSource();

    // initialize detectors
    MDetectorManager * detm = MDetectorManager::instance();

    detm->addDetector(new MFibersStackDetector("FibersStack"));

    detm->initTasks();
    detm->initParameterContainers();
    detm->initCategories();

    // initialize tasks
    MTaskManager * tm = MTaskManager::instance();
    tm->initTasks();

    // go over all events
    for (int i=0 ; i < ev_limit; ++i)
    {
        dataManager->clear();

        dataManager->getEntry(i);

        tm->runTasks();

        dataManager->fill();
    }

    tm->finalizeTasks();

    dataManager->save();

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

    std:vector< std::pair<std::string, int> > digi_status;
    while (optind < argc)
    {
        std::cout << "Digitize " << argv[optind] << std::endl;
        int status = simdst(argv[optind], events);
        std::string f = argv[optind];
        digi_status.push_back({f, status});
        ++optind;
    }

    for (int i = 0; i < digi_status.size(); ++i)
    {
        std::cout << "Digitizer for " << digi_status[i].first << " with status " << digi_status[i].second << std::endl;
//         std::cout << "Output file is " << oname.Data() << std::endl;
    }

    return 0;
}
