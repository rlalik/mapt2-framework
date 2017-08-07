#include "MGeantTrack.h"

ClassImp(MGeantTrack);

MGeantTrack::MGeantTrack()
{
    clear();
}

void MGeantTrack::clear()
{
    TVector3 p(0,0,0);

    start.x = 0.;
    start.y = 0.;
    start.z = 0.;
    start.px = 0.;
    start.py = 0.;
    start.pz = 0.;
    start.E = -1000.;

    stop.x = 0.;
    stop.y = 0.;
    stop.z = 0.;
    stop.px = 0.;
    stop.py = 0.;
    stop.pz = 0.;
    stop.E = -1000.;

    scattering                          = false;
    processes.clear();
    g4Id                                = 0;
    stopInDetector                      = false;
    secondariesID.clear();
    trackID                             = 0;
    parentID                            = -1;
    generationProcess                   = "";
    inAcceptance                        = kFALSE;
    proc_arr[COMPTON]                   = kFALSE;
    proc_arr[INELASTIC]                 = kFALSE;
    proc_arr[ATREST]                    = kFALSE;
}

void MGeantTrack::addProcess(string name)
{
    processes.push_back(name);
}


void MGeantTrack::addDaughterID(Int_t ID)
{
    secondariesID.push_back(ID);
}

Double_t MGeantTrack::getDistance() const
{
    TVector3 end_ = TVector3(stop.x, stop.y, stop.z) - TVector3(0, 36, 0);
    return end_.Mag();
}

Double_t MGeantTrack::getRange() const
{
    if (!stopInDetector)
        return -100.;

    TVector3 sta = TVector3(start.x, start.y, start.z) - TVector3(0, 36, 0);
    TVector3 sto = TVector3(stop.x, stop.y, stop.z) - TVector3(0, 36, 0);

    TVector3 psta = TVector3(start.px, start.py, start.pz);
    TVector3 psto = TVector3(stop.px, stop.py, stop.pz);

    psta *= 1.0/psta.Mag();
    psto *= 1.0/psto.Mag();

    Double_t t = 0.0;

    const Double_t limit = 36.0;
    while (true)
    {
        if (
            (fabs(sta.X() + t * psta.X()) < limit) and
            (fabs(sta.Y() + t * psta.Y()) < limit) and
            (fabs(sta.Z() + t * psta.Z()) < limit) )
        {
            break;
        }

        t += 0.1;
    }

    TVector3 intsec(sta + psta * t);

//     printf("start = %f,%f,%f\n", sta.X(), sta.Y(), sta.Z());
//     printf("  end = %f,%f,%f\n", end.X(), end.Y(), end.Z());
//     printf("  int = %f,%f,%f\n", intsec.X(), intsec.Y(), intsec.Z());
    return (intsec - sto).Mag();
}

void MGeantTrack::print() const
{
    TVector3 psta = TVector3(start.px, start.py, start.pz);
    TVector3 psto = TVector3(stop.px, stop.py, stop.pz);

    psta *= 1.0/psta.Mag();
    psto *= 1.0/psto.Mag();

    printf("##### particle #####\n");
    printf("  pos sta=(%f,%f,%f)  sto=(%f,%f,%f)\n", start.x, start.y, start.z, stop.x, stop.y, stop.z);
    printf("  dir sta=(%f,%f,%f)  sto=(%f,%f,%f)\n", psta.X(), psta.Y(), psta.Z(), psto.X(), psto.Y(), psto.Z());
    printf("  start energy = %f,  stop energy = %f\n", start.E, stop.E);
    printf("  scat=%d  process=", scattering);
    for (Int_t i = 0; i < processes.size(); ++i)
        printf("%s,", processes[i].c_str());
    printf("\n");
    printf("  PID=%d  stop in det=%d\n", g4Id, stopInDetector);
    printf("  num of sec=%d\n", secondariesID.size());
    //   std::vector<Int_t> secondaries_ID;
    //   Int_t particle_ID;
    //   string generationProcess;
    //   Double_t startEnergy;
    //   Double_t endEnergy;
}

void MGeantTrack::Clear(Option_t* options)
{
    clear();
}
