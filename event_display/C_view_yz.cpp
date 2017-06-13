#include "C_view_yz.h"
#include <QtGui>



//
// Konstruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
C_view_yz::C_view_yz(QWidget *parent, DataManager *d) :
    QWidget(parent)
{
    //
    // Default Werte festlegen
    //

    // Zeiger auf Datenobjekt
    dataManager = d;

    normfactor = 20;

    m_mouse_x = 0;
    m_mouse_y = 0;

    // Kaestchengroesse festlegen
    m_breite = (width() - 60)/30;
    m_hoehe =  (height() - 110)/30;


    // Hintergrundfarbe setzen
    QPalette Pal;
    Pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(Pal);

    // MouseTracking On
    setMouseTracking(true);
}
// ----------------------------------------------------------------------------------------------------------------------------------
// Konstruktor ENDE






//
// PaintEvent -> Zeichnet 2D Ansicht
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_yz::paintEvent(QPaintEvent *)
{
    if (!dataManager->getEvent())
        return;

    // Painter anlegen
    QPainter painter(this);


    // Kaestchengroesse festlegen
    m_breite = (width() - 110)/30;
    m_hoehe = (height() - 110)/30;

    // Mouse-Position in fiber Koordinaten umrechnen
    int fiber_x = -1;   // Wenn Mouse nicht ueber einer Fiber liegt, dann ist Wert von fiber_x = -1
    int fiber_y = -1;   // Wenn Mouse nicht ueber einer Fiber liegt, dann ist Wert von fiber_y = -1


    if ((m_mouse_x != 0) && (m_mouse_y != 0))
    {
        fiber_x = ((m_mouse_x-(15+m_breite+5))/m_breite);
        fiber_y = (((m_mouse_y-30)/m_hoehe)+1);

        if (fiber_y%2 == 0)
        {
            fiber_y = -1;
            fiber_x = -1;
        }

    }






    //
    //  Informationen anzeigen -> Bei MouseOver wird Fiberposition und Fiberwert angezeigt
    //


    QString s;      // In String s werden Texte vor dem Zeichnen eingetragen


    if ((fiber_x != -1) && (fiber_y != -1))     // Mouse ueber einem Kaestchen -> Position und Wert in s
    {
        s = "y position: " + QString::number(fiber_x) +"\nz position: " + QString::number(fiber_y)
           +"\nvalue: "  + QString::number(dataManager->getEvent()->getHits()->getValue(fiber_x,fiber_y) );
    }

    else                                         // Mouse nicht ueber einem Kaestchen
    {
        s = "y position: \nz position: \nvalue: " ;
    }

    // Zeichnen des Textes in s
    QRect r(15,30+m_hoehe+30* m_hoehe,150,50);
    painter.setFont(QFont("Times", 10, QFont::Normal));
    painter.drawText(r, Qt::AlignLeft | Qt::TextWordWrap, s);

    //
    //  Informationen anzeigen ENDE



    //
    //  Fiber und Beschriftung zeichnen
    //

    // Alle Fiber durchgehen
    for (int y = 0; y<15; y++)
    {

        for (int x=0; x <30;x++)
        {

            // Farbe einstellen
            float color;
            color = dataManager->getEvent()->getHits()->getZYValue(x,y)/normfactor;

            if (color >1)
            {
                color = 1;
            }


            if (color != 0)     // Wenn color != 0 -> Wert ist nicht 0 -> Farbe einstellen
            {
                painter.setBrush(QBrush(QColor( (int)(255*color), (int)(255*(1-color)), 0 )));

                painter.setPen(QColor( 255, 255,255 ));

            }
            else                // Wenn color == 0 -> Wert ist 0 -> Grau einstellen
            {
                painter.setBrush(QBrush(QColor(190,190,190)));

                painter.setPen(QColor(255,255,255));
            }

            // Kaestchen zeichnen
            painter.drawRect(15+ m_breite + 5 +x*m_breite,30+y*2*m_hoehe,m_breite,m_hoehe);

        }

        // Farbe auf Schwarz setzen
        painter.setPen(QColor(0,0,0));

        // Beschriftung z-Achse
        QString s = QString::number((y*2+1));
        QRect r(15,30 + y*2*m_hoehe,m_breite,m_hoehe);
        painter.setFont(QFont("Times", 10, QFont::Normal));
        painter.drawText(r, Qt::AlignCenter | Qt::TextWordWrap, s);

    }

    // Beschriftung x-Achse
    for (int x=0; x <15;x++)
    {

        QString t = QString::number(2*x);
        QRect r(15+m_breite +5+x*2*m_breite,15,m_breite,m_hoehe);
        painter.setFont(QFont("Times", 10, QFont::Normal));
        painter.drawText(r, Qt::AlignCenter | Qt::TextWordWrap, t);

    }

    //
    //  Fiber und Beschriftung zeichnen ENDE



    //
    // Legende fuer Farben
    //

    // Farbverlauf zeichnen
    QLinearGradient farbverlauf(QPointF(60+30*m_breite + m_breite, 30+m_hoehe*5), QPointF(60+30*m_breite + m_breite, 30+m_hoehe*5+m_hoehe*20));
    farbverlauf.setColorAt(0,QColor(255,0,0));
    farbverlauf.setColorAt(0.5,QColor(0.5*255,0.5*255,0));
    farbverlauf.setColorAt(1,QColor(0,255,0));
    QRect leg(60+30*m_breite,30+m_hoehe*5,m_breite*2,m_hoehe*20);
    painter.fillRect(leg,farbverlauf);

    // Hoechstwert Farbverlauf Beschriftung
    QString t = QString::number(normfactor);
    QRect rect_H(60+30*m_breite+ m_breite*2+5,30+m_hoehe*5 -0.5*m_hoehe,m_breite*1.5,m_hoehe*1.5);
    painter.setFont(QFont("Times", 10, QFont::Normal));
    painter.drawText(rect_H, Qt::AlignCenter | Qt::TextWordWrap, t);

    // Kleinster Wert Farbverlauf Beschriftung
    t = QString::number(0.1);
    QRect rect_U(60+30*m_breite+ m_breite*2+5,m_hoehe*20+30+m_hoehe*5 -0.5*m_hoehe,m_breite*1.5,m_hoehe*1.5);
    painter.setFont(QFont("Times", 10, QFont::Normal));
    painter.drawText(rect_U, Qt::AlignCenter | Qt::TextWordWrap, t);

    // Haelfte Farbverlauf Beschriftung
    t = QString::number(normfactor/2);
    QRect rect_M(60+30*m_breite+ m_breite*2+5,m_hoehe*10+30+m_hoehe*5 -0.5*m_hoehe,m_breite*1.5,m_hoehe*1.5);
    painter.setFont(QFont("Times", 10, QFont::Normal));
    painter.drawText(rect_M, Qt::AlignCenter | Qt::TextWordWrap, t);

}
// ----------------------------------------------------------------------------------------------------------------------------------
// PaintEvent ENDE





//
// Mouseposition holen und 2D-View updaten
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_view_yz::mouseMoveEvent(QMouseEvent *event)
{
    m_mouse_x = event->x();     // aktuelle x-Koordinate der Mouse
    m_mouse_y = event->y();     // aktuelle y-Koordinate der Mouse

    // Wenn Mouse nicht in relevantem Fensterbereich -> Position auf (0,0) -> Kein Mouse-Over
    if (((m_mouse_x < 15+m_breite+5) || (m_mouse_x > 20+m_breite+30*m_breite)) || ((m_mouse_y < 30) || (m_mouse_y > 30+ 30*m_hoehe)) )
    {
        m_mouse_x = 0;
        m_mouse_y = 0;
    }

    update();       // Ruft paintevent auf -> Aktuallisierung von Mouse-Over-Anzeige
}
// ----------------------------------------------------------------------------------------------------------------------------------
// mouseMoveEvent ENDE


//
// Destruktor
// ----------------------------------------------------------------------------------------------------------------------------------
C_view_yz::~C_view_yz()
{

}
// ----------------------------------------------------------------------------------------------------------------------------------
// Destruktor ENDE
