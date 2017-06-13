#include "C_quader.h"

//
// Konstruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
C_Quader::C_Quader()
{
    x = 0;
    y = 0;
    z = 0;

    standard = 0.0666;  		// Standardbreite und -hoehe einer Fiber in der 3D-Repraesentation: 30 Fiber in der Richtung, Wurfelkante in openGL-Koordinaten 2
					// -> 2/30 = 0.0667 -> standard = 0.0666
    // Anfangswerte setzen					
    l = standard;
    b = standard;
    h = standard;

    r = 1;
    g = 1;
    bl= 1;
    a =0.5;

    // Anfangswerte in vertices und alpha_colors speichern
    update();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// Konstruktor ENDE


//
// setColor
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_Quader::setColor(float r1, float g1, float bl1, float a1)
{
    // Farbwerte werden uebergeben, gespeichert und vertices und alpha_colors aktualisiert
    r = r1;
    g = g1;
    bl = bl1;
    a = a1;

    update();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// setColor ENDE


//
// setGeometrie
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_Quader::setGeometrie(double l1, double b1, double h1)
{
    // Laenge, Hoehe und Breite werden uebergeben, gespeichert und vertices und alpha_colors aktualisiert
    l = l1;
    b = b1;
    h = h1;

    update();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// setGeometrie ENDE



//
// setPosition
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_Quader::setPosition(double x1, double y1, double z1)
{
    // x,y,z werden uebergeben, gespeichert und vertices und alpha_colors aktualisiert
    x = x1;
    y = y1;
    z = z1;

    update();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// setPosition ENDE


//
// update
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_Quader::update()
{
    // Vectoren zu beginn loeschen
    vertices.clear();
    color_alpha.clear();
    
    // Vectoren neu befuellen
    
    vertices << QVector3D(x+l,y-h,z-b) << QVector3D(x,y-h,z) << QVector3D(x+l,y-h,z)
             << QVector3D(x+l,y-h,z-b)  << QVector3D(x,y-h,z-b) << QVector3D(x,y-h,z)       //Unterseite
             << QVector3D(x+l,y,z) << QVector3D(x,y-h,z) << QVector3D(x,y,z)
             << QVector3D(x+l,y,z) << QVector3D(x+l,y-h,z) << QVector3D(x,y-h,z)            //Vorderseite
             << QVector3D(x,y,z) << QVector3D(x,y-h,z) << QVector3D(x,y-h,z-b)
             << QVector3D(x,y,z) << QVector3D(x,y-h,z-b) << QVector3D(x,y,z-b)              //Links
             << QVector3D(x,y,z-b) << QVector3D(x,y-h,z-b) << QVector3D(x+l,y,z-b)
             << QVector3D(x+l,y,z-b) << QVector3D(x,y-h,z-b) << QVector3D(x+l,y-h,z-b)      //Hinten
             << QVector3D(x+l,y,z-b) << QVector3D(x+l,y-h,z-b) << QVector3D(x+l,y-h,z)
             << QVector3D(x+l,y,z-b) << QVector3D(x+l,y-h,z) << QVector3D(x+l,y,z)          //Rechts
             << QVector3D(x+l,y,z) << QVector3D(x,y,z-b) << QVector3D(x+l,y,z-b)
             << QVector3D(x+l,y,z) << QVector3D(x,y,z) << QVector3D(x,y,z-b);               //Oben

    color_alpha << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a)
                << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a) << QVector4D(r,g,bl,a);

}
// ----------------------------------------------------------------------------------------------------------------------------------
// update ENDE



//
// getTriangle
// ----------------------------------------------------------------------------------------------------------------------------------
//
QVector<QVector3D> C_Quader::getTriangle()
{
    return vertices;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getTriangle ENDE


//
// getColors
// ----------------------------------------------------------------------------------------------------------------------------------
//
QVector<QVector4D> C_Quader::getColors()
{
    return color_alpha;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getColors ENDE



//
// xzFiber
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_Quader::xzFiber(int x_pos, int z_pos, float r1, float g1, float bl1, float a1)
{
    // Uebergebene Farbwerte speichern
    r = r1;
    g = g1;
    bl = bl1;
    a = a1;

    // x,y,z fuer xz-Fiber in openGL-Koordinaten berechnen
    x =-1+ x_pos*standard;
    y = 1- z_pos*2*standard;
    z = 1;

    // Geometrie festlegen
    l = standard;
    h = standard;
    b = 2;

    update();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// xzFiber ENDE


//
// yzFiberr
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_Quader::yzFiber(int x_pos, int z_pos, float r1, float g1, float bl1, float a1)
{
    // Uebergebene Farbwerte speichern
    r = r1;
    g = g1;
    bl = bl1;
    a = a1;

    // x,y,z fuer xz-Fiber in openGL-Koordinaten berechnen
    z =-1+ x_pos*standard;
    y = 1-standard- z_pos*2*standard;
    x = -1;

    // Geometrie festlegen
    b = standard;
    h = standard;
    l = 2;

    update();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// yzFiber ENDE
