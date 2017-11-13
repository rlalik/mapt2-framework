#include "C_view_2D.h"
#include <QtGui>

#include "MGeantTrack.h"
#include "MGeantFibersRaw.h"

float energy_color_scale = 20.0;

C_view_2D::C_view_2D(PLANE plane, MMAPTManager* d, QWidget *parent) :
    pl(plane), QWidget(parent)
{
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

    switch (pl)
    {
        case XY:
            u_lab = "x";
            v_lab = "z";
            break;
        case ZY:
            u_lab = "y";
            v_lab = "z";
            break;
        default:
            u_lab = "u";
            v_lab = "v";
            break;
    }
}

void C_view_2D::paintEvent(QPaintEvent *)
{
    MCategory * catGeantFibersRaw = dataManager->getCategory(MCategory::CatGeantFibersRaw);
    if (!catGeantFibersRaw)
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
        bool res = false;
        switch (pl)
        {
            case XY:
                fiber_y = (((m_mouse_y-30)/m_hoehe)+1);
                res = (fiber_y%2 == 0);
                break;
            case ZY:
                fiber_y = (((m_mouse_y-30)/m_hoehe));
                res = (fiber_y%2 != 0);
                break;
            default:
                break;
        }

        if (res)
        {
            fiber_y = -1;
            fiber_x = -1;
        }
    }

    QString s;  // In String s werden Texte vor dem Zeichnen eingetragen

    if ((fiber_x != -1) && (fiber_y != -1))     // Mouse ueber einem Kaestchen -> Position und Wert in s
    {
        QString val("0");
        MLocator loc(2);
        loc[0] = 0;
        loc[1] = (29-fiber_y) * 30 + (29-fiber_x);
        MGeantFibersRaw * p = (MGeantFibersRaw *)catGeantFibersRaw->getObject(loc);
        if (p)
            val = QString::number(p->getEnergyLoss());

        s = u_lab + " position: " + QString::number(29-fiber_x) +"\n" + v_lab + " position: " + QString::number(29-fiber_y)
            +"\nvalue: " + val;
    }
    else    // Mouse nicht ueber einem Kaestchen
    {
        s = u_lab + " position: \n" + v_lab + " position: \nvalue: " ;
    }

    // Zeichnen des Textes in s
    QRect r(15,30+m_hoehe+30* m_hoehe,150,50);
    painter.setFont(QFont("Times", 10, QFont::Normal));
    painter.drawText(r, Qt::AlignLeft | Qt::TextWordWrap, s);

    int _x, _y;

    // Alle Fiber durchgehen
    for (int y = 0; y < 15; ++y)
    {
        for (int x = 0; x < 30; ++x)
        {
            switch (pl)
            {
                case XY:
                    _x = x;
                    // since we count down, +1 must be on x not on y
                    _y = 29 - (y*2+1);
                    break;
                case ZY:
                    _x = x;
                    _y = 29 - (y*2);
                    break;
            }

            // Farbe einstellen
            float color = 0;

            MLocator loc(2);
            loc[0] = 0;
            loc[1] = _y * 30 + _x;

            MGeantFibersRaw * p = (MGeantFibersRaw *)catGeantFibersRaw->getObject(loc);
            if (p)
                color = p->getEnergyLoss()/energy_color_scale;

            if (color > 1)
                color = 1;

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
            painter.drawRect(15 + m_breite + 5 + (29-x)*m_breite, 30 + y*2*m_hoehe,m_breite,m_hoehe);
        }

        // Farbe auf Schwarz setzen
        painter.setPen(QColor(0,0,0));

        // Beschriftung z-Achse
        QString s;
        s = QString::number(_y); 
        QRect r(15,30 + y*2*m_hoehe,m_breite,m_hoehe);
        painter.setFont(QFont("Times", 10, QFont::Normal));
        painter.drawText(r, Qt::AlignCenter | Qt::TextWordWrap, s);
    }

    // Beschriftung x-Achse
    for (int x = 0; x < 15; ++x)
    {
        QString t = QString::number(29-(2*x));
        QRect r(15+m_breite +5+x*2*m_breite,15,m_breite,m_hoehe);
        painter.setFont(QFont("Times", 10, QFont::Normal));
        painter.drawText(r, Qt::AlignCenter | Qt::TextWordWrap, t);
    }

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

void C_view_2D::mouseMoveEvent(QMouseEvent *event)
{
    m_mouse_x = event->x();     // aktuelle x-Koordinate der Mouse
    m_mouse_y = event->y();     // aktuelle y-Koordinate der Mouse

    // Wenn Mouse nicht in relevantem Fensterbereich -> Position auf (0,0) -> Kein Mouse-Over
    if (((m_mouse_x < 15+m_breite+5) || (m_mouse_x > 20+m_breite+30*m_breite)) || ((m_mouse_y < 30) || (m_mouse_y > 30+ 30*m_hoehe)) )
    {
        m_mouse_x = 0;
        m_mouse_y = 0;
    }

    update();   // Ruft paintevent auf -> Aktuallisierung von Mouse-Over-Anzeige
}

C_view_2D::~C_view_2D()
{
}
