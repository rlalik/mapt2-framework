#include "B1Particle.hh"

// Needed for Creation of shared libs
ClassImp(B1Particle);

B1Particle::B1Particle()
{
    clear();
}

void B1Particle::clear()
{
    TVector3 p(0,0,0);
    
    startPosition                       = p;
    endPosition                         = p;
    startDirection                      = p;
    endDirection                        = p;
    scattering                          = false;
    processes.clear();
    g4Number                            = 0;
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

void B1Particle::random()
{
    
    Double_t x = getRandomNumber()*10;
    Double_t y = getRandomNumber()*10;
    Double_t z = getRandomNumber()*10;
    
    TVector3 p(x,y,z);
    
    startPosition                       = p;
    endPosition                         = p;
    startDirection                      = p;
    endDirection                        = p;
    scattering                          = false;
    g4Number                            = 1;
    stopInDetector                      = false;
    secondariesID.push_back((Int_t) getRandomNumber()*100);
    trackID                             = (Int_t)getRandomNumber()*100;
    parentID                            = -1;
    inAcceptance                        = kFALSE;
    proc_arr[COMPTON]                   = kFALSE;
    proc_arr[INELASTIC]                 = kFALSE;
    proc_arr[ATREST]                    = kFALSE;
}

Double_t B1Particle::getRandomNumber()
{
    return randGen.Rndm();
}

void B1Particle::addProcess(string name)
{
    processes.push_back(name);
}


void B1Particle::addDaughterID(Int_t ID)
{
    secondariesID.push_back(ID);
}

Double_t B1Particle::getDistance() const
{
    TVector3 end_ = endPosition - TVector3(0, 36, 0);
    return end_.Mag();
}

Double_t B1Particle::getRange() const
{
    if (!stopInDetector)
        return -100.;

    TVector3 sta = startPosition - TVector3(0, 36, 0);
    TVector3 end = endPosition - TVector3(0, 36, 0);

    Double_t t = 0.0;

    const Double_t limit = 36.0;
    while (true)
    {
        if (
            (fabs(sta.X() + t * startDirection.X()) < limit) and
            (fabs(sta.Y() + t * startDirection.Y()) < limit) and
            (fabs(sta.Z() + t * startDirection.Z()) < limit) )
        {
            break;
        }

        t += 0.1;
    }

    TVector3 intsec(sta + startDirection * t);

//     printf("start = %f,%f,%f\n", sta.X(), sta.Y(), sta.Z());
//     printf("  end = %f,%f,%f\n", end.X(), end.Y(), end.Z());
//     printf("  int = %f,%f,%f\n", intsec.X(), intsec.Y(), intsec.Z());
    return (intsec - end).Mag();
}

void B1Particle::print() const
{
    printf("##### particle #####\n");
    printf("  pos sta=(%f,%f,%f)  sto=(%f,%f,%f)\n", startPosition.X(), startPosition.Y(), startPosition.Z(),
           endPosition.X(), endPosition.Y(), endPosition.Z());
    printf("  dir sta=(%f,%f,%f)  sto=(%f,%f,%f)\n", startDirection.X(), startDirection.Y(), startDirection.Z(),
           endDirection.X(), endDirection.Y(), endDirection.Z());
    
    printf("  scat=%d  process=", scattering);
    for (Int_t i = 0; i < processes.size(); ++i)
        printf("%s,", processes[i].c_str());
    printf("\n");
    printf("  PID=%d  stop in det=%d\n", g4Number, stopInDetector);
    printf("  num of sec=%d\n", secondariesID.size());
    //   std::vector<Int_t> secondaries_ID;
    //   Int_t particle_ID;
    //   string generationProcess;
    //   Double_t startEnergy;
    //   Double_t endEnergy;
}
