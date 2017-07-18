#ifndef C_VIEW_2D_H
#define C_VIEW_2D_H

#include "C_data.h"
#include <QtGui>
#include <QWidget>

// MAPT Framework
#include "MDataManager.h"

class C_view_2D : public QWidget
{
    Q_OBJECT
public:
    enum PLANE { XZ, YZ };

    explicit C_view_2D(PLANE plane, MDataManager* d, QWidget *parent = 0);
    ~C_view_2D();

private:

    int m_mouse_x;
    int m_mouse_y;

    MDataManager* dataManager;

    float m_breite;             // Breite eines Kaestchens. Festgelegt durch Fenstergroesse, Abstand zum Fensterrand.
    float m_hoehe;              // Hoehe eines Kaestchens. Festgelegt durch Fenstergroesse, Abstand zum Fensterrand.

    float normfactor;

    PLANE pl;
    QString u_lab, v_lab;

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // C_VIEW_2D_H
