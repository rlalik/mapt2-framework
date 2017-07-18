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
#include "MGeantFibersRaw.h"
#include "MGeantTrack.h"

#include "MDataManager.h"

using namespace std;

int analysis(const std::string & file, int events = 1000)
{
    TString oname = file;

    if (oname.EndsWith(".root"))
        oname.ReplaceAll(".root", "_ana.root");
    else
        oname.Append("_ana.root");

    MDataManager * dataManager = MDataManager::instance();
    dataManager->setSimulation(true);
    dataManager->setInputFileName(file);
    dataManager->open();
    dataManager->openCategory(MCategory::CatGeantTrack);
    dataManager->openCategory(MCategory::CatGeantFibersRaw);
    dataManager->setOutputFileName(oname.Data());
    dataManager->book();

    TH1I * h_pi_mult = new TH1I("h_pi_mult", "h_pi_mult", 20, 0, 20);
    TH1I * h_pim_mult = new TH1I("h_pim_mult", "h_pim_mult", 10, 0, 10);
    TH1I * h_pip_mult = new TH1I("h_pip_mult", "h_pip_mult", 10, 0, 10);
    TH1I * h_piz_mult = new TH1I("h_piz_mult", "h_piz_mult", 10, 0, 10);
    TH1I * h_pic_mult = new TH1I("h_pic_mult", "h_pic_mult", 10, 0, 10);

    TH1I * h_pi_mult_1stgen = new TH1I("h_pi_mult_1stgen", "h_pi_mult_1stgen", 20, 0, 20);
    TH1I * h_pim_mult_1stgen = new TH1I("h_pim_mult_1stgen", "h_pim_mult_1stgen", 10, 0, 10);
    TH1I * h_pip_mult_1stgen = new TH1I("h_pip_mult_1stgen", "h_pip_mult_1stgen", 10, 0, 10);
    TH1I * h_piz_mult_1stgen = new TH1I("h_piz_mult_1stgen", "h_piz_mult_1stgen", 10, 0, 10);
    TH1I * h_pic_mult_1stgen = new TH1I("h_pic_mult_1stgen", "h_pic_mult_1stgen", 10, 0, 10);

    TH1I * h_acc = new TH1I("h_acc", "h_acc", 5, 0, 5);

    TH1I * h_range = new TH1I("h_range", "h_range", 220, 0, 110);
    TH1I * h_distance = new TH1I("h_distance", "h_distance", 200, 0, 100);

    int ev_limit = events < dataManager->getEntriesFast() ? events : dataManager->getEntriesFast();
    std::cout << dataManager->getEntriesFast() << " events, analyze " << ev_limit << std::endl;

    int secs = 0;
    for (int i=0 ; i < ev_limit; ++i)
    {
        dataManager->getEntry(i);
        MCategory * catGeantTrack = dataManager->getCategory(MCategory::CatGeantTrack);
        if (!catGeantTrack)
        {
            std::cerr << "event NULL" << "\n";
            return -1;
        }
//         std::cout << event->getSimulatedEvent()->getPrimary()->Get_stop_in_detector() << "\n";
//         event->getSimulatedEvent()->getPrimary()->print();

        size_t tracks_num = catGeantTrack->getEntries();
        if (tracks_num == 0)
            continue;

        MCategory * catGeantFibersRaw = dataManager->getCategory(MCategory::CatGeantFibersRaw);
        if (!catGeantFibersRaw)
        {
            std::cerr << "event NULL" << "\n";
            return -1;
        }

        h_acc->Fill(0);

        MLocator loc_track(1);
        int sec_num = tracks_num - 1;
        bool prim_stop_in_det = false;

        for (int t = 0; t < tracks_num; ++t)
        {
            loc_track[0] = t;
            MGeantTrack * track = (MGeantTrack*) catGeantTrack->getObject(loc_track);

            if (track->getTrackID() == 1)
            {
                if (track->getInAcceptance())
                    h_acc->Fill(1);
                if (track->getStopInDetector())
                {
                    h_acc->Fill(2);
                    h_range->Fill(track->getRange());
                    h_distance->Fill(track->getDistance());
                }

                prim_stop_in_det = track->getStopInDetector();
                // nothing more to do for primary track
                continue;
            }

            int pim_mult = 0;
            int pip_mult = 0;
            int piz_mult = 0;
            int pic_mult = 0;
            int pim_mult_1stgen = 0;
            int pip_mult_1stgen = 0;
            int piz_mult_1stgen = 0;
            int pic_mult_1stgen = 0;

            if (prim_stop_in_det)
            {
//                 std::cout << "Number of secs: "<< event->getSimulatedEvent()->getSecondaries().size() << "\n\n";
                secs += sec_num;

                for (int i = 0; i < sec_num; ++i)
                {
                    if (track->isPim())
                    {
                        ++pim_mult;
                        ++pic_mult;
                    }
                    else if (track->isPip())
                    {
                        ++pip_mult;
                        ++pic_mult;
                    }
                    else if (track->isPiz())
                        ++piz_mult;

                    if (track->getParentID() == 1)
                    {
                        if (track->isPim())
                        {
                            ++pim_mult_1stgen;
                            ++pic_mult_1stgen;
                        }
                        else if (track->isPip())
                        {
                            ++pip_mult_1stgen;
                            ++pic_mult_1stgen;
                        }
                        else if (track->isPiz())
                            ++piz_mult_1stgen;
                    }
                }

                Int_t pi_all = pim_mult + pim_mult + piz_mult;
                h_pi_mult->Fill(pi_all);
                h_pim_mult->Fill(pim_mult);
                h_pip_mult->Fill(pip_mult);
                h_piz_mult->Fill(piz_mult);
                h_pic_mult->Fill(pic_mult);

                Int_t pi_all_1stgen = pim_mult_1stgen + pim_mult_1stgen + piz_mult_1stgen;
                h_pi_mult_1stgen->Fill(pi_all_1stgen);
                h_pim_mult_1stgen->Fill(pim_mult_1stgen);
                h_pip_mult_1stgen->Fill(pip_mult_1stgen);
                h_piz_mult_1stgen->Fill(piz_mult_1stgen);
                h_pic_mult_1stgen->Fill(pic_mult_1stgen);
            }
        }

        if (prim_stop_in_det)
            dataManager->fill();
    }

//     dataManager.save();

    std::cout << "Number of secs total: " << secs << "\n";

    h_pi_mult->Write();
    h_pim_mult->Write();
    h_pip_mult->Write();
    h_piz_mult->Write();
    h_pic_mult->Write();

    h_pi_mult_1stgen->Write();
    h_pim_mult_1stgen->Write();
    h_pip_mult_1stgen->Write();
    h_piz_mult_1stgen->Write();
    h_pic_mult_1stgen->Write();

    h_acc->Write();

    h_range->Write();
    h_distance->Write();

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
