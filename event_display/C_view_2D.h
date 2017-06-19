#ifndef C_VIEW_2D_H
#define C_VIEW_2D_H

#include "C_data.h"
#include <QtGui>
#include <QWidget>

// MAPT Framework
#include "DataManager.hh"
#include "Event.h"

class C_view_2D : public QWidget
{
    Q_OBJECT
public:
    explicit C_view_2D(QWidget *parent = 0, DataManager* d = 0);
    ~C_view_2D();


private:

    int m_mouse_x;
    int m_mouse_y;

    DataManager* dataManager;

    float m_breite;             // Breite eines Kaestchens. Festgelegt durch Fenstergroesse, Abstand zum Fensterrand.
    float m_hoehe;              // Hoehe eines Kaestchens. Festgelegt durch Fenstergroesse, Abstand zum Fensterrand.

    float normfactor;

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:

};

#endif // C_VIEW_2D_H
