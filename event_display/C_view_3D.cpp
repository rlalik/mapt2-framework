#include "C_view_3D.h"
#include <QtGui>
#include <QDebug>

// MAPT-framework
#include "MDataManager.h"
#include "MGeantFibersRaw.h"
#include "MGeantTrack.h"

C_view_3D::C_view_3D(MDataManager* da, QWidget *parent) :
    dataManager(da), QGLWidget(parent)
{
    geometry = new UserGeant4Geometry("geometry.txt",true);

    geometry->construct();

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

void C_view_3D::resizeGL(int w, int h)
{
    // Perspektive bei Groessenaenderung des Fensters beibehalten
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) w / (float) h, 0.001, 1000);

    glViewport (0,0, w, h);

    // Koordinatensystem unten im Eck halten
    coordinates->move(0,height()-coordinates->height());

}

void C_view_3D::mousePressEvent(QMouseEvent *event_)
{
    // Position eintragen, an der Mouse gedrueckt wird.
    lastPos = event_->pos();
    event_->accept();
}

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

void C_view_3D::update3D()
{
    // Alle Listen leeren
    line.clear();
    colors.clear();
    fibers.clear();
    color_fibers.clear();
    end_point.clear();
    end_point_color.clear();

    MCategory * catGeantTrack = dataManager->getCategory(MCategory::CatGeantTrack);
    MCategory * catGeantFibersRaw = dataManager->getCategory(MCategory::CatGeantFibersRaw);

    if (!catGeantTrack)
    {
        return;
    }
    else
    {
        size_t secs_num = catGeantTrack->getEntries();
        MLocator loc1(1);

        for (uint i = 0; i < secs_num; ++i)
        {
            loc1[0] = i;
            MGeantTrack * p = (MGeantTrack *)catGeantTrack->getObject(loc1);

            QVector3D sta(p->getStartPosition().X(), p->getStartPosition().Y(), p->getStartPosition().Z());
            QVector3D sto(p->getEndPosition().X(), p->getEndPosition().Y(), p->getEndPosition().Z());

            line << sta << sto;
            end_point << sto;

            QVector3D col;

            if (p->getTrackID() == 1)
            {
                col = QVector3D(1,1,1);
            }
            else
            {
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
            }

            colors << col << col;
            end_point_color << col;
        }

        // Fiber einzeichnen
        size_t fibers_num = catGeantFibersRaw->getEntries();

        for (uint i = 0; i < secs_num; ++i)
        {
            MGeantFibersRaw * p = (MGeantFibersRaw *)catGeantTrack->getObject(i);

            int y = p->getY();
            int x = p->getX();

            // set color
            float color;
            color = p->getEnergy()/20.0;
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
