#ifndef QUADER_H
#define QUADER_H


#include <QtGui>

class C_Quader
{
public:
    C_Quader();

    void setPosition(double x1, double y1, double z1);
    void setColor (float r1,float g1,float bl1, float a1);
    void setGeometrie (double l1, double b1, double h1);

    QVector<QVector3D> getTriangle ();
    QVector<QVector4D> getColors ();

    void update();

    void xzFiber(int x_pos, int z_pos, float r1,float g1,float bl1, float a1);
    void yzFiber(int x_pos, int z_pos, float r1,float g1,float bl1, float a1);

private:

    double x,y,z,l,b,h,standard;
    float r,g,bl,a;

    QVector<QVector3D> vertices;
    QVector<QVector4D> color_alpha;
};

#endif // QUADER_H
