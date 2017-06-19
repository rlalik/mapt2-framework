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
}

void B1Particle::random()
{
    
    double x = getRandomNumber()*10;
    double y = getRandomNumber()*10;
    double z = getRandomNumber()*10;
    
    TVector3 p(x,y,z);
    
    startPosition                       = p;
    endPosition                         = p;
    startDirection                      = p;
    endDirection                        = p;
    scattering                          = false;
    g4Number                            = 1;
    stopInDetector                      = false;
    secondariesID.push_back((int) getRandomNumber()*100);
    trackID                             = (int)getRandomNumber()*100;
    parentID                            = -1;
}

double B1Particle::getRandomNumber()
{
    return randGen.Rndm();
}

void B1Particle::addProcess(string name)
{
    processes.push_back(name);
}


void B1Particle::addDaughterID(int ID)
{
    secondariesID.push_back(ID);
}

void B1Particle::print() const
{
    printf("##### particle #####\n");
    printf("  pos sta=(%f,%f,%f)  sto=(%f,%f,%f)\n", startPosition.X(), startPosition.Y(), startPosition.Z(),
           endPosition.X(), endPosition.Y(), endPosition.Z());
    printf("  dir sta=(%f,%f,%f)  sto=(%f,%f,%f)\n", startDirection.X(), startDirection.Y(), startDirection.Z(),
           endDirection.X(), endDirection.Y(), endDirection.Z());
    
    printf("  scat=%d  process=", scattering);
    for (int i = 0; i < processes.size(); ++i)
        printf("%s,", processes[i].c_str());
    printf("\n");
    printf("  PID=%d  stop in det=%d\n", g4Number, stopInDetector);
    printf("  num of sec=%d\n", secondariesID.size());
    //   std::vector<int> secondaries_ID;
    //   int particle_ID;
    //   string generationProcess;
    //   double startEnergy;
    //   double endEnergy;
}
