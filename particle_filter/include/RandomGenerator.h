#ifndef RandomGenerator_h
#define RandomGenerator_h

// STL inculdes
#include <iostream>
#include <cmath>

// root includes
#include <TRandom.h>


//! \brief Wraps the root random generator.
/*!
  Can be used to switch to another random generator to replace root.
*/
class RandomGenerator {
public:
    static RandomGenerator* getInstance();
    void setSeed (double seed_);

    double getRandomGaussian (double mean, double sigma);
    double uniform ();

private:
    RandomGenerator ();
    ~RandomGenerator () {;};

    static RandomGenerator* instance;
};

#endif
