#include "Particle.h"


Particle::Particle ()
{
}


Particle::Particle (TVector3 pIn_, TVector3 pOut_, double eIn_, double eOut_)
{
    pIn = pIn_;
    pOut = pOut_;
    eIn = eIn_;
    eOut = eOut_;
}


Particle::~Particle()
{

}

void Particle::set (TVector3 pIn_, TVector3 pOut_, double eIn_, double eOut_)
{
    pIn = pIn_;
    pOut = pOut_;
    eIn = eIn_;
    eOut = eOut_;
}

void Particle::set (Particle* p)
{
    pIn = p->getpIn();
    pOut = p->getpOut();
    eIn = p->geteIn();
    eOut = p->geteOut();
}

TVector3 Particle::getDir ()
{
    TVector3 dir = pOut - pIn;
    dir.SetMag(1);
    return dir;
}

void Particle::print ()
{
    std::cout << "Particle: " << "\n";
    std::cout << "pIn: ";
    pIn.Print();
    std::cout << "pOut: ";
    pOut.Print();
    std::cout << "Direction: ";
    TVector3 dir = pOut - pIn;
    dir.SetMag(1);
    dir.Print();
    std::cout << "eIn: " << eIn << "\n";
    std::cout << "eOut: " << eOut << "\n";
    std::cout << "\n";
}

bool Particle::isSame (Particle* p)
{
    if ( (pIn == p->getpIn()) && (pOut == p->getpOut()) && (eIn == p->geteIn()) && (eOut == p->geteOut()) )
    {
        return true;
    }
    return false;
}
