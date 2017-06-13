#include "C_view_3D.h"
#include <QtGui>
#include <QDebug>

//
// Konstruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
C_view_3D::C_view_3D(QWidget *parent, DataManager* da) :
    QGLWidget(parent)
{
    geometry = new UserGeant4Geometry("geometry.txt",true);

    geometry->construct();

    // Anfangswerte belegen
    dataManager = da;

    if (da == NULL)
    {
        qDebug()<<"Null";
    }

    alpha = 250;
    beta = -20;
    distance = 200;

    // Koordinatensystem erzeugen
    coordinates = new C_view_coordinatesystem (this);
    coordinates->move(0,0);

    double dx = 35;
    double dy = 35;
    double dz = 35;
    double shiftZ = 0;
    double shiftY = 35;
    // Wuerfelkanten anlegen
    wire << QVector3D(-dx,-dy+shiftY,-dz+shiftZ) << QVector3D(-dx,-dy+shiftY,-dz+shiftZ)
         << QVector3D(-dx,-dy+shiftY,-dz+shiftZ) << QVector3D(-dx,dy+shiftY,-dz+shiftZ)
         << QVector3D(-dx,dy+shiftY,-dz+shiftZ) << QVector3D(dx,dy+shiftY,-dz+shiftZ)
         << QVector3D(-dx,dy+shiftY,-dz+shiftZ) << QVector3D(-dx,dy+shiftY,dz+shiftZ)
         << QVector3D(dx,dy+shiftY,-dz+shiftZ) << QVector3D(dx,-dy+shiftY,-dz+shiftZ)
         << QVector3D(dx,dy+shiftY,-dz+shiftZ) << QVector3D(dx,dy+shiftY,dz+shiftZ)
         << QVector3D(dx,-dy+shiftY,-dz+shiftZ) << QVector3D(-dx,-dy+shiftY,-dz+shiftZ)
         << QVector3D(dx,-dy+shiftY,-dz+shiftZ) << QVector3D(dx,-dy+shiftY,dz+shiftZ)
         << QVector3D(dx,-dy+shiftY,dz+shiftZ) << QVector3D(-dx,-dy+shiftY,dz+shiftZ)
         << QVector3D(-dx,-dy+shiftY,dz+shiftZ) << QVector3D(-dx,dy+shiftY,dz+shiftZ)
         << QVector3D(-dx,dy+shiftY,dz+shiftZ) << QVector3D(dx,dy+shiftY,dz+shiftZ)
         << QVector3D(dx,dy+shiftY,dz+shiftZ) << QVector3D(dx,-dy+shiftY,dz+shiftZ)
         << QVector3D(-dx,-dy+shiftY,-dz+shiftZ) << QVector3D(-dx,-dy+shiftY,dz+shiftZ);

    // Farben fuer Wuerfelkanten (wird momentan verwendet)
    for (int i = 0; i < 26; i++) {
        wire_color << QVector3D(0.5,0.6,0.6);
    }

}


//
// Konstruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_3D::initializeGL()
{
    // Initialisierung der 3D Umgebung
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);

    // Shaderprogramme einbinden
    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
    shaderProgram.link();

}
// ----------------------------------------------------------------------------------------------------------------------------------
// Konstruktor ENDE


//
// paintGL
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_3D::paintGL()
{
    // Vor dem Zeichnen alle Daten aktuallisieren
    update3D();

    // Einstellungen vor dem Zeichnen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );


    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;


    // Kamera einstellen
    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha,0,1,0);
    cameraTransformation.rotate(beta,1,0,0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0,0, distance);
    QVector3D cameraDirection = cameraTransformation * QVector3D (0,1,0);

    vMatrix.lookAt(cameraPosition,QVector3D(0,35,0), cameraDirection);


    // Shaderprogramme einbinden
    shaderProgram.bind();

    shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);



    // Tracks als Linien einzeichnen
    shaderProgram.setAttributeArray("vertex", line.constData());
    shaderProgram.enableAttributeArray("vertex");

    shaderProgram.setAttributeArray("color", colors.constData());
    shaderProgram.enableAttributeArray("color");

    glLineWidth(2.0f);

    glDrawArrays(GL_LINES, 0, line.size());
    //

    // Endpoint der Tracks zeichnen
    glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
    shaderProgram.setAttributeArray("vertex", end_point.constData());
    shaderProgram.enableAttributeArray("vertex");

    //shaderProgram.setAttributeArray("color", end_point_color.constData());
    //shaderProgram.enableAttributeArray("color");

    glPointSize(7.0f);

    glDrawArrays(GL_POINTS, 0, end_point.size());
    //

    // Wuerfelkanten zeichnen
    shaderProgram.setAttributeArray("vertex", wire.constData());
    shaderProgram.enableAttributeArray("vertex");

    shaderProgram.setAttributeArray("color", wire_color.constData());
    shaderProgram.enableAttributeArray("color");

    glLineWidth(1.0f);

    glDrawArrays(GL_LINES, 0, wire.size());
    //


    // aktive Fiber zeichnen
    shaderProgram.setAttributeArray("vertex", fibers.constData());
    shaderProgram.enableAttributeArray("vertex");

    shaderProgram.setAttributeArray("color", color_fibers.constData());
    shaderProgram.enableAttributeArray("color");

    glDrawArrays(GL_TRIANGLES, 0, fibers.size());
    //


    // Shaderprogramme ausbinden
    shaderProgram.disableAttributeArray("vertex");
    shaderProgram.disableAttributeArray("color");
    shaderProgram.release();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// paintGL ENDE


//
// resizeGL
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_3D::resizeGL(int w, int h)
{
    // Perspektive bei Groessenaenderung des Fensters beibehalten
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) w / (float) h, 0.001, 1000);

    glViewport (0,0, w, h);

    // Koordinatensystem unten im Eck halten
    coordinates->move(0,height()-coordinates->height());

}
// ----------------------------------------------------------------------------------------------------------------------------------
// resizeGL ENDE


//
// mousePressEvent
// ----------------------------------------------------------------------------------------------------------------------------------
//
 void C_view_3D::mousePressEvent(QMouseEvent *event_)
  {
     // Position eintragen, an der Mouse gedrueckt wird.
     lastPos = event_->pos();
     event_->accept();
  }
  // ----------------------------------------------------------------------------------------------------------------------------------
  // mousePressEvent ENDE


//
// mouseMoveEvent
// ----------------------------------------------------------------------------------------------------------------------------------
//
 void C_view_3D::mouseMoveEvent(QMouseEvent *event_)
 {
     // Differenz zwischen Position an der Mouse gedrueckt wurde und aktueller Position
     int deltaX = event_->x() - lastPos.x();
     int deltaY = event_->y() - lastPos.y();

     // Umrechnung der Positionsaenderung in Winkelaenderungen
     if (event_->buttons() & Qt::LeftButton)
     {
         alpha -= deltaX;
         while (alpha < 0)
         {
             alpha += 360;
         }
         while (alpha >= 360)
         {
             alpha -= 360;
         }

         beta -= deltaY;
         if (beta < -90)
         {
             beta = -90;
         }
         if (beta > 90)
         {
             beta = 90;
         }

         coordinates->up(alpha,beta);
         updateGL();
     }


     lastPos = event_->pos();

     event_->accept();
 }
 // ----------------------------------------------------------------------------------------------------------------------------------
 // mouseMoveEvent ENDE


//
// wheelEvent
// ----------------------------------------------------------------------------------------------------------------------------------
//
 void C_view_3D::wheelEvent(QWheelEvent *event_)
 {
    // Zoomen mit Mouserad
    int delta = event_->delta();

    if (event_->orientation() == Qt::Vertical)
     {
         if (delta < 0)
         {
             distance *= 1.2;
         }
         else if (delta > 0)
         {
             distance *= 0.9;
         }

         if (distance < 2) distance = 2;
         if (distance > 250) distance = 250;

         updateGL();
     }
     event_->accept();
 }
 // ----------------------------------------------------------------------------------------------------------------------------------
 // wheelEvent ENDE



//
// update3D
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_3D::update3D()
{
    // Alle Listen leeren
    line.clear();
    colors.clear();
    fibers.clear();
    color_fibers.clear();
    end_point.clear();
    end_point_color.clear();

    event = dataManager->getEvent();
    if (!event)
        return;

    EventSim* simEv = event->getSimulatedEvent();
    if (!simEv)
    {

    }
    else {
        // Tracks einzeichnen und Endpunkte zeichnen
        for (int i = 0; i< 1; i++)					// Alle Tracks im Event durchgehen
        {
            QVector3D startPos (simEv->getPrimary()->getStartPosition().X(),simEv->getPrimary()->getStartPosition().Y(),simEv->getPrimary()->getStartPosition().Z());
            QVector3D endPos (simEv->getPrimary()->getEndPosition().X(),simEv->getPrimary()->getEndPosition().Y(),simEv->getPrimary()->getEndPosition().Z());

            line << startPos << endPos;		// in line alle Start- und Endpositionen speichern

            end_point << endPos;						// Endpositionen in end_points speichern


            colors << QVector3D(1,1,1) << QVector3D(1,1,1);
            end_point_color << QVector3D(1,1,1) ;
        }

        vector<B1Particle*> secs = simEv->getSecondaries();
        size_t secs_num = secs.size();

        for (uint i = 0; i < secs_num; ++i)
        {
            B1Particle * p = secs[i];
            QVector3D sta(p->getStartPosition().X(), p->getStartPosition().Y(), p->getStartPosition().Z());
            QVector3D sto(p->getEndPosition().X(), p->getEndPosition().Y(), p->getEndPosition().Z());

            line << sta << sto;
            end_point << sto;

            QVector3D col;
            int geant_id = p->getG4Number();
            switch (geant_id)
            {
                case 211:
                    col = QVector3D(1,0,0);
                    break;
                case -211:
                    col = QVector3D(0,1,0);
                    break;
                case 111:
                    col = QVector3D(0,0,1);
                    break;
                default:
                    col = QVector3D(0,0,0);
                    break;
            }

            colors << col << col;
            end_point_color << col;
        }

        // Fiber einzeichnen

        for (int y = 0; y<30; y++) {
            for (int x=0; x <30;x++) {

                // set color
                float color;
                color = event->getHits()->getValue(x,y)/20;
                if (color >1)
                    color = 1;

                // paint only hits
                if (color != 0) {
                    AbsPart* part = dynamic_cast<AbsPart*> (geometry->getFiber(x,y));
                    std::vector<TVector3> verticesPart = part->getVertices();
                    std::vector<std::vector<int> > trianglesPart =part->getTriangles();

                    // for each triangle
                    // for(int tri=0;tri<part->getNumberTriangle();tri++)
                    for(int tri=0;tri<trianglesPart.size();tri++) {
                        // for each vertex
                        for (int i=0;i<trianglesPart[tri].size();i++) {
                            int num = trianglesPart[tri].at(i);
                            TVector3 vec = verticesPart[num];
                            fibers << QVector3D(vec.X(),vec.Y(),vec.Z());
                            if (color != 0)
                                color_fibers << QVector4D(color,1-color,0,0.9);
                            else
                                color_fibers << QVector4D(1,1,1,0.01);
                        }
                    }
                }

            }
        }
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------
// update3D ENDE


//
// Destruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
C_view_3D::~C_view_3D()
{

    delete coordinates;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// Destruktor ENDE
