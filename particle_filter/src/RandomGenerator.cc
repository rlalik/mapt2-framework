#include "RandomGenerator.h"


RandomGenerator::RandomGenerator()
{
    gRandom->SetSeed(21);
}

RandomGenerator* RandomGenerator::getInstance ()
{
    if (instance == NULL)
        instance = new RandomGenerator();
    return instance;
}

RandomGenerator* RandomGenerator::instance = new RandomGenerator ();

void RandomGenerator::setSeed (double seed_)
{
    gRandom->SetSeed(seed_);
}


double RandomGenerator::getRandomGaussian (double mean, double sigma)
{
    return gRandom->Gaus(mean,std::sqrt(sigma));
}

double RandomGenerator::uniform ()
{
    return gRandom->Uniform();
}
