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
}

double B1Particle::getRandomNumber()
{
    return randGen.Rndm();
}


TVector3 B1Particle::getStartPosition() const
{
    return startPosition;
}

void B1Particle::setStartPosition(TVector3 p)
{
    startPosition = p;
}


TVector3 B1Particle::getEndPosition() const
{
    return endPosition;
}

void B1Particle::setEndPosition(TVector3 p)
{
    endPosition = p;
}

TVector3 B1Particle::getStartDirection() const
{
    return startDirection;
}

void B1Particle::setStartDirection(TVector3 p)
{
    startDirection = p;
}

TVector3 B1Particle::getEndDirection() const
{
    return endDirection;
}

void B1Particle::setEndDirection(TVector3 p)
{
    endDirection = p;
}

bool B1Particle::getScattering() const
{
    return scattering;
}

void B1Particle::setScattering(bool b)
{
    scattering = b;
}

std::vector<string> B1Particle::getProcesses() const
{
    return processes;
}

void B1Particle::setProcesses(const std::vector<string> & v)
{
    processes = v;
}

int B1Particle::getG4Number() const
{
    return g4Number;
}

void B1Particle::setG4Number(int i)
{
    g4Number = i;
}

bool B1Particle::getStopInDetector() const
{
    return stopInDetector;
}

void B1Particle::setStopInDetector(bool b)
{
    stopInDetector = b;
}

int B1Particle::getTrackID() const
{
    return trackID;
}

void B1Particle::setTrackID(int i)
{
    trackID = i;
}

string B1Particle::getGenerationProcess() const
{
    return generationProcess;
}

void B1Particle::setGenerationProcess(string i)
{
    generationProcess = i;
}


void B1Particle::addProcess(string name)
{
    processes.push_back(name);
}


void B1Particle::addDaughterID(int ID)
{
    secondariesID.push_back(ID);
}


double B1Particle::getStartEnergy() const
{
    return startEnergy;
}

void B1Particle::setStartEnergy(double i)
{
    startEnergy = i;
}


double B1Particle::getEndEnergy() const
{
    return endEnergy;
}

void B1Particle::setEndEnergy(double i)
{
    endEnergy = i;
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
