#ifndef Hits30x30_h
#define Hits30x30_h

#include <iostream>

#include "TROOT.h"

class TObject;

//! \brief Data structure representing an the 900 fiber measurements of an event.
/*!

*/
class Hits30x30: public TObject {
public:
    //! \brief Constructor. Initializes the array[30][30] with 0.
    Hits30x30 ();

    //! \brief Constructor. Initializes the array[30][30] with the provided array.
    Hits30x30 (double hitMatrix[30][30]);

    //! \brief Constructor. Initializes the array[30][30] with the provided Hits30x30 object.
    Hits30x30 (Hits30x30* hits_);
    ~Hits30x30 () {;};

    //! \brief Prints the array in the terminal.
    void print ();
    double getValue (int x, int y);

    //! \brief Returns a normalized copy of this instance.
    Hits30x30* getNormalized (double norm);

    //! \brief Returns a copy of this instance, where values greater 0 become 1 and the rest 0.
    Hits30x30* getBitImage ();

    //! \brief Set value at the provided position.
    void setValue (int x, int y, double value);

    //! \brief Initializes the array[30][30] with 0.
    void clear ();

    //! \brief Initializes the array[30][30] with the provided Hits30x30 object.
    void set (Hits30x30* hits_);

    //! \brief Initializes the array[30][30] with the provided array.
    void set (double hitMatrix[30][30]);

    double getXYValue (int x, int y);
    double getZYValue (int z, int y);

    double getMaxValue ();

    //! \brief Returns number of hits.
    int getNumberOfHits ();

    //! \brief Needed for creation of shared library.
    ClassDef(Hits30x30, 1);

private:
    //! \brief The array representing the 900 values.
    double matrix [30][30];

};

#endif
