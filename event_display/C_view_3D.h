#ifndef VIEW3D_H
#define VIEW3D_H

#include <QGLWidget>
#include <QtGui>
#include <QGLShaderProgram>
#include "C_data.h"
#include "C_quader.h"
#include "C_view_coordinatesystem.h"
#include <iostream>

// geometry shared library
#include <G4ThreeVector.hh>
#include <UserGeant4Geometry.h>
#include <AbsPart.h>
#include <CADPart.h>
#include <CADFiber.h>
#include <vector>
#include <TVector3.h>

class MDataManager;

class C_view_3D : public QGLWidget
{
    Q_OBJECT
public:
    explicit C_view_3D(MDataManager* da, QWidget *parent = 0);
    ~C_view_3D();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void update3D();

private:
    //G4ThreeVector geometry;
    UserGeant4Geometry* geometry;

    QPoint lastPos;

    int alpha;
    int beta;
    double distance;

    MDataManager* dataManager;
    C_view_coordinatesystem* coordinates;

    QMatrix4x4 pMatrix;
    QGLShaderProgram shaderProgram;

    QVector<QVector3D> vertices;        // Wuerfelflaechen zeichnen
    QVector<QVector3D> line;            // Tracks zeichnen
    QVector<QVector3D> wire;            // Wurfelkanten
    QVector<QVector3D> fibers;          // Fiber zeichnen
    QVector<QVector3D> end_point;       // Endpunkt zeichnen

    QVector<QVector4D> color_fibers;    // Farbe Fiber
    QVector<QVector3D> colors;          // Farbe Tracks
    QVector<QVector3D> wire_color;      // Farbe Wuerfelkanten
    QVector<QVector4D> color_alpha;     // Farbe Wuerfelflaechen
    QVector<QVector4D> end_point_color; // Farbe Endpunkt

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif // VIEW3D_H
