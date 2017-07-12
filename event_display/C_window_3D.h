#ifndef WINDOW3D_H
#define WINDOW3D_H

#include <QMainWindow>
#include "C_data.h"
#include "C_view_3D.h"

// MAPT-framework
#include "Hits30x30.h"

class DataManager;
class GeantSim;

class C_window_3D : public QMainWindow
{
    Q_OBJECT

public:
    explicit C_window_3D(QWidget *parent = 0,DataManager * da=0);
    ~C_window_3D();
    void update();


private:

    QVBoxLayout* m_layout;
    QHBoxLayout* m_layout1;

    QLabel* m_l1;
    QLabel* m_l2;
    QLabel* m_l3;

    C_view_3D* m_view3D;

    DataManager* dataManager;

protected:


};

#endif // WINDOW3D_H
