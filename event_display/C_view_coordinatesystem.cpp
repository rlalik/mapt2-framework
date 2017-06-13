#include "C_view_coordinatesystem.h"

//
// Konstruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
C_view_coordinatesystem::C_view_coordinatesystem(QWidget *parent) :
    QGLWidget(parent)
{
    // Anfangswerte setzen
    alpha = 0;
    beta = 0;
    distance = 3;

    resize(150,150);
}
// ----------------------------------------------------------------------------------------------------------------------------------
// Konstruktor ENDE



//
// initializeGL
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_coordinatesystem::initializeGL()
{
    // 3D-Szene initialisieren
    glClearColor(0.2,0.2,0.2,1);

    glEnable(GL_DEPTH_TEST);

    // Shader einbinden
    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
    shaderProgram.link();


    // Linien des Koordinatensystems zeichnen
    wire << QVector3D(1,0,0) << QVector3D(0,0,0)
         << QVector3D(0,1,0) << QVector3D(0,0,0)
         << QVector3D(0,0,1) << QVector3D(0,0,0);
    
    // Linienfarben (weiss)
    wire_color << QVector3D(1,1,1) << QVector3D(1,1,1)
               << QVector3D(1,1,1) << QVector3D(1,1,1)
               << QVector3D(1,1,1) << QVector3D(1,1,1);

    // Endpunkte der Linien farblich markieren, da keine BEschriftung moeglich
    end_point << QVector3D(1,0,0) << QVector3D(0,1,0) << QVector3D(0,0,1);
    end_color << QVector3D(0,1,1) << QVector3D(0,0,1) << QVector3D(1,1,0);


}
// ----------------------------------------------------------------------------------------------------------------------------------
// initializeGL ENDE


//
// paintGL
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_coordinatesystem::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );


    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;


    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha,0,1,0);
    cameraTransformation.rotate(beta,1,0,0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0,0, distance);
    QVector3D cameraDirection = cameraTransformation * QVector3D (0,1,0);

    vMatrix.lookAt(cameraPosition,QVector3D(0,0,0), cameraDirection);

    shaderProgram.bind();

    shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);


    //Endpunkte
    shaderProgram.setAttributeArray("vertex", end_point.constData());
    shaderProgram.enableAttributeArray("vertex");

    shaderProgram.setAttributeArray("color", end_color.constData());
    shaderProgram.enableAttributeArray("color");

    glPointSize(5.0f);

    glDrawArrays(GL_POINTS, 0, end_point.size());
    //


    // Wire drawing
    shaderProgram.setAttributeArray("vertex", wire.constData());
    shaderProgram.enableAttributeArray("vertex");

    shaderProgram.setAttributeArray("color", wire_color.constData());
    shaderProgram.enableAttributeArray("color");

    glLineWidth(1.0f);

    glDrawArrays(GL_LINES, 0, wire.size());
    //



    shaderProgram.disableAttributeArray("vertex");
    shaderProgram.disableAttributeArray("color");
    shaderProgram.release();

}
// ----------------------------------------------------------------------------------------------------------------------------------
// paintGL ENDE-


//
// resizeGL
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_coordinatesystem::resizeGL(int w, int h)
{
    // 3D-Szene bei Groessenaenderung regeln
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) w / (float) h, 0.001, 1000);

    glViewport (0,0, w, h);

}
// ----------------------------------------------------------------------------------------------------------------------------------
// resizeGL ENDE


//
// up
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_coordinatesystem::up(int a, int b)
{
    // Wird in C_view_3D der Kamerablickwinkel geaendert, so wird diese Funktion aufgerufen, um den gleichen Blickwinkel auch im Koordinatensystem zu haben
    alpha = a;
    beta = b;

    updateGL();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// up ENDE


//
// Destruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
C_view_coordinatesystem::~C_view_coordinatesystem()
{
}
// ----------------------------------------------------------------------------------------------------------------------------------
// Destruktor ENDE
