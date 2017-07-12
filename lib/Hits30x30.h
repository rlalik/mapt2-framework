#ifndef HITS30X30_H
#define HITS30X30_H

#include <iostream>

#include "TROOT.h"

//! \brief Data structure representing an the 900 fiber measurements of an event.
/*!

*/
template<class T>
class Hits30x30
{
private:
    //! \brief The array representing the 900 values.
    T matrix [30][30];

public:
    //! \brief Constructor. Initializes the array[30][30] with 0.
    Hits30x30();
    virtual ~Hits30x30() {}

    //! \brief Prints the array in the terminal.
    void print() const;
    T getValue(int x, int y) const;

    //! \brief Returns a normalized copy of this instance.
    Hits30x30<T> getNormalized(double norm) const;

    //! \brief Returns a copy of this instance, where values greater 0 become 1 and the rest 0.
    Hits30x30<T> getBitImage() const;

    //! \brief Set value at the provided position.
    void setValue(int x, int y, T value);

    //! \brief Add value at the provided position.
    void addValue(int x, int y, T value);

    //! \brief Initializes the array[30][30] with 0.
    void clear();

    //! \brief Initializes the array[30][30] with the provided Hits30x30 object.
    void set(const Hits30x30<T> & hits_);

    //! \brief Initializes the array[30][30] with the provided array.
    void set(const T hitMatrix[30][30]);

    T getXYValue(int x, int y) const;
    T getZYValue(int z, int y) const;

    T getMaxValue() const;

    //! \brief Returns number of hits.
    int getNumberOfHits() const;

    Hits30x30<T> operator+(const Hits30x30<T> & d);
    Hits30x30<T> operator+=(const Hits30x30<T> & d);
    Hits30x30<T> operator/=(T d);

    //! \brief Needed for creation of shared library.
    ClassDef(Hits30x30, 1);
};

template <class T> Hits30x30<T>::Hits30x30()
{
    // fill matrix with 0
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            matrix[x][y] = 0;
        }
    }
}

template <class T> void Hits30x30<T>::print() const
{
    printf("Print hits at 0x%x of 0x%x\n", &matrix, this);
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            std::cout << matrix[x][y]  << " ";
        }
        std::cout << "\n";
    }
}

template <class T> void Hits30x30<T>::setValue(int x, int y, T value)
{
    if ((x>=0) && (x<30) && (y>=0) && (y<30))
    {
        matrix[x][y] = value;
    }
}

template <class T> void Hits30x30<T>::addValue(int x, int y, T value)
{
    if ((x>=0) && (x<30) && (y>=0) && (y<30))
    {
        matrix[x][y] += value;
    }
}

template <class T> T Hits30x30<T>::getValue(int x, int y) const
{
    if ((x>=0) && (x<30) && (y>=0) && (y<30))
    {
        return matrix[x][y];
    }
    return -1.;
}

template <class T> Hits30x30<T> Hits30x30<T>::getBitImage() const
{
    Hits30x30 bitImage;
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            if (matrix[x][y] > 0)
            {
                bitImage.setValue(x,y,1.0);
            }
        }
    }
    return bitImage;
}

template <class T> Hits30x30<T> Hits30x30<T>::getNormalized(double norm) const
{
    if (norm == 0)
    {
        std::cout << "Norm can not be 0" << "\n";
        return *this;
    }
    Hits30x30<T> normalized;
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            normalized.setValue(x, y, matrix[x][y]/norm);
        }
    }
    return normalized;
}

template <class T> void Hits30x30<T>::clear()
{
    // fill matrix with 0
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            matrix[x][y] = 0;
        }
    }
}

template <class T> void Hits30x30<T>::set(const Hits30x30 & hits_)
{
    // fill matrix from hits_
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            matrix[x][y] = hits_.getValue(x,y);
        }
    }
}

template <class T> void Hits30x30<T>::set(const T hitMatrix[30][30])
{
    // fill matrix from hitMatrix
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            matrix[x][y] = hitMatrix[x][y];
        }
    }
}


template <class T> T Hits30x30<T>::getXYValue(int x, int y) const
{
    if ((x>=0) && (x<30) && (y>=0) && (y<15))
    {
        return matrix[x][y*2];
    }
    return -1.;
}

template <class T>  T Hits30x30<T>::getZYValue(int z, int y) const
{
    if ((z>=0) && (z<30) && (y>=0) && (y<15))
    {
        return matrix[z][y*2+1];
    }
    return -1.;
}

template <class T> T Hits30x30<T>::getMaxValue() const
{
    T max = 0;
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            if (matrix[x][y] > max)
                max = matrix[x][y];
        }
    }
    return max;
}

template <class T> int Hits30x30<T>::getNumberOfHits() const
{
    int num = 0;
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            if (matrix[x][y] > 0)
                num++;
        }
    }
    return num;
}

template <class T> Hits30x30<T> Hits30x30<T>::operator+(const Hits30x30<T>& d)
{
    Hits30x30<T> h;
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            h.matrix[x][y] = matrix[x][y] + d.matrix[x][y];
        }
    }
    return h;
}

template <class T> Hits30x30<T> Hits30x30<T>::operator+=(const Hits30x30<T>& d)
{
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            matrix[x][y] += d.matrix[x][y];
        }
    }
    return *this;
}

template <class T> Hits30x30<T> Hits30x30<T>::operator/=(T d)
{
    for (int y = 0; y < 30; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            matrix[x][y] /= d;
        }
    }
    return *this;
}

#endif /* HITS30X30_H */
