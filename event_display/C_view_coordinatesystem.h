#ifndef VIEWCOORDINATESYSTEM_H
#define VIEWCOORDINATESYSTEM_H

#include <QGLWidget>
#include <QtGui>
#include <QGLShaderProgram>
#include "C_data.h"
#include "C_quader.h"

class C_view_coordinatesystem : public QGLWidget
{
    Q_OBJECT
public:
    explicit C_view_coordinatesystem(QWidget *parent = 0);
    ~C_view_coordinatesystem();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void up(int a, int b);



private:
    int alpha;
    int beta;
    double distance;

    QMatrix4x4 pMatrix;
    QGLShaderProgram shaderProgram;


    QVector<QVector3D> wire;            // Wurfelkanten
    QVector<QVector3D> end_point;       // Endpunkt zeichnen

    QVector<QVector3D> wire_color;      // Farbe Wuerfelkanten
    QVector<QVector3D> end_color;       // Farbe Endpunkte



protected:


public slots:



signals:


};

#endif // VIEWCOORDINATESYSTEM_H
