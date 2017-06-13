#include "Hits30x30.h"

// Needed for Creation of shared libs
ClassImp(Hits30x30);

Hits30x30::Hits30x30 ()
{
    // fill matrix with 0
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            matrix[x][y] = 0;
        }
    }
}

Hits30x30::Hits30x30 (Hits30x30* hits_)
{
    // fill matrix from hits_
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            matrix[x][y] = hits_->getValue(x,y);
        }
    }
}

Hits30x30::Hits30x30 (double hitMatrix[30][30])
{
    // fill matrix from hitMatrix
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            matrix[x][y] = hitMatrix[x][y];
        }
    }
}

void Hits30x30::print ()
{
    // print
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            std::cout << matrix[x][y]  << " ";
        }
        std::cout << "\n";
    }
}

void Hits30x30::setValue (int x, int y, double value)
{
    if ((x>=0) && (x<30) && (y>=0) && (y<30))
    {
        matrix[x][y] = value;
    }
}

double Hits30x30::getValue (int x, int y)
{
    if ((x>=0) && (x<30) && (y>=0) && (y<30))
    {
        return matrix[x][y];
    }
    return -1.;
}

Hits30x30* Hits30x30::getBitImage ()
{
    Hits30x30* bitImage = new Hits30x30();
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            if (matrix[x][y] > 0)
            {
                bitImage->setValue(x,y,1.0);
            }
        }
    }
    return bitImage;
}

Hits30x30* Hits30x30::getNormalized (double norm)
{
    if (norm == 0)
    {
        std::cout << "Norm can not be 0" << "\n";
        return NULL;
    }
    Hits30x30* normalized = new Hits30x30();
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            normalized->setValue(x,y,matrix[x][y]/norm);
        }
    }
    return normalized;
}

void Hits30x30::clear ()
{
    // fill matrix with 0
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            matrix[x][y] = 0;
        }
    }
}

void Hits30x30::set (Hits30x30* hits_)
{
    // fill matrix from hits_
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            matrix[x][y] = hits_->getValue(x,y);
        }
    }
}

void Hits30x30::set (double hitMatrix[30][30])
{
    // fill matrix from hitMatrix
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            matrix[x][y] = hitMatrix[x][y];
        }
    }
}


double Hits30x30::getXYValue (int x, int y)
{
    if ((x>=0) && (x<30) && (y>=0) && (y<15))
    {
        return matrix[x][y*2];
    }
    return -1.;
}

double Hits30x30::getZYValue (int z, int y)
{
    if ((z>=0) && (z<30) && (y>=0) && (y<15))
    {
        return matrix[z][y*2+1];
    }
    return -1.;
}



double Hits30x30::getMaxValue ()
{
    double max = 0;
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            if (matrix[x][y] > max)
                max = matrix[x][y];
        }
    }
    return max;
}

int Hits30x30::getNumberOfHits ()
{
    int num = 0;
    for (int y=0; y<30; y++)
    {
        for (int x=0; x<30; x++)
        {
            if (matrix[x][y] > 0)
                num++;
        }
    }
    return num;
}
