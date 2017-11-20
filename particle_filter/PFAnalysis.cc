// STL inculdes
#include <iostream>
#include <chrono>
#include <time.h>

#include <getopt.h>

// root includes
#include <TVector3.h>

// geant4 includes


// MAPT-Analysis framework includes
#include <UserCGALGeometry.h>
#include <UserGeant4Geometry.h>
#include <MMAPTManager.h>
#include <MDetectorManager.h>
#include <MFibersStackDetector.h>
#include <MTaskManager.h>

// includes
#include "ParticleFilter.h"


using namespace std;
using namespace std::chrono;

//! \brief Main to start the analysis with the particle filter.
/*!
 We define several parameters to provide to the main. So it is possible to use this
 main in cluster runs.

 We define the following parameters:
 - jobnumber: (jobnumber-1000) = event number to start with
 - path to data file
 - path to output directory
 - number of events, which should be analyzed in this run
*/
int main(int argc,char** argv)
{
    int jobNumber = 0;
    int numberOfEventsAnalyzed = 1;
    int test_particles_number = 10000;
    string data;
    string savePath = "output";
    string geo_file = "geometry.txt";

    int c;
    while(1)
    {
        static struct option long_options[] = {
            { "job", required_argument, 0, 'j' },
            { "jobsnumber", required_argument, 0, 'k' },
            { "events", required_argument, 0, 'e' },
            { "output", required_argument, 0, 'o' },
            { "geometry", required_argument, 0, 'g' },
            { "ntest", required_argument, 0, 'n' },
            { 0, 0, 0, 0 }
        };

        int option_index = 0;

        c = getopt_long(argc, argv, "e:g:j:k:n:o:", long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {
            case 'e':
                numberOfEventsAnalyzed = atoi(optarg);
                break;
            case 'g':
                geo_file = optarg;
                break;
            case 'j':
                jobNumber = atoi(optarg);
                break;
            case 'k':
                numberOfEventsAnalyzed = atoi(optarg);
                break;
            case 'n':
                test_particles_number = atoi(optarg);
                break;
            case 'o':
                savePath = optarg;
                break;
            default:
                break;
        }
    }

    if (optind < argc)
    {
        while (optind < argc)
        {
            data  = argv[optind];
            ++optind;
            break;
        }
    }
    else
    {
        std::cerr << "No input file" << std::endl;
    }

    std::cerr << "use standard arguments" << "\n";
    std::cout << jobNumber << "\n";
    std::cout << numberOfEventsAnalyzed << "\n";
    std::cout << "path to data file: " << data  << "\n";
    std::cout << "path to save file: " << savePath  << "\n";

    TString oname = data;
    TString pfname = data;

    if (oname.EndsWith(".root"))
    {
        oname.ReplaceAll(".root", "_pf.root");
        pfname.ReplaceAll(".root", "");
    }
    else
        oname.Append("_pf.root");

    MMAPTManager * dataManager = MMAPTManager::instance();
    dataManager->setSimulation(true);
    dataManager->setInputFileName(data);
    dataManager->open();

    // initialize parameters
    MParManager * pm = MParManager::instance();
    pm->setParamSource("params.txt");
    pm->parseSource();

    // initialize detectors
    MDetectorManager * detm = MDetectorManager::instance();

    detm->addDetector(new MFibersStackDetector("FibersStack"));
    detm->initParameterContainers();
    detm->initCategories();

    dataManager->openCategory(MCategory::CatGeantTrack);
    dataManager->openCategory(MCategory::CatGeantFibersRaw);
    dataManager->openCategory(MCategory::CatFibersStackCal);
    dataManager->setOutputFileName(oname.Data());
    dataManager->book();

    string s = data;

    UserCGALGeometry* geometry = new UserCGALGeometry(geo_file.c_str(), false);
    geometry->construct();

    // event loop
    for (int i = jobNumber; i < jobNumber+numberOfEventsAnalyzed; ++i)
    {
        if (i%1000 == 0)
        {
            std::cout << "Event: " << i << "\n";
        }
        RandomGenerator::getInstance()->setSeed(i+1000);

        // generate save file name
        string savePathPrior = savePath + "Prior" + to_string(i) + ".root";
        char buff[200];
        sprintf(buff, "%s_pf_e%06d.root", pfname.Data(), i);
        string savePath_ = buff;

        // get the current entry
        dataManager->getEntry(i);

        // FIXME
//         // // print MC truth
//         std::cout << "MC start position: ";
//         dataManager.getEvent()->getSimulatedEvent()->getPrimary()->Get_start_position().Print();
//         std::cout << "MC start direction: ";
//         dataManager.getEvent()->getSimulatedEvent()->getPrimary()->Get_start_direction().Print();
//         std::cout << "MC start energy: " << dataManager.getEvent()->getSimulatedEvent()->getPrimary()->Get_start_energy() << "\n";


        // initialize the particle filter with this event
        double deltaE = 5;
        double deltaPos = 3;
        double deltaDir = 3;

        ParticleFilter* particleFilter = new ParticleFilter(geometry, test_particles_number);
        particleFilter->initEvent(dataManager, deltaE, deltaPos, deltaDir);

        // clock for time measurement -> runtime of one event
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        // set the measurement noise for the forward filter
        particleFilter->setEvalSigma(0.5);

        // run the forward filter
        bool worked = particleFilter->filter();
        std::cout << "\n" << "\n";

        // if the forward filter was successfull start backward filtering
        if (worked)
        {
            std::cout << "\n" << "\n";
            // set the measurement noise for the backward filter
            particleFilter->setEvalSigma(0.05);
            // run the backward filter
            if(particleFilter->backFilter())
            {
                // stop the time needed for analysis of this event
                high_resolution_clock::time_point t2 = high_resolution_clock::now();
                auto duration = duration_cast<seconds>( t2 - t1 ).count();
                std::cout << "time: " << duration << "\n";
                double time = duration;
                // write the output of the filter (the PDFs and runtime) to a file
                particleFilter->createBackPosteriors(savePath_,time);
            }
        }
        // delete the particle filter for this event
        delete particleFilter;
    }
}
