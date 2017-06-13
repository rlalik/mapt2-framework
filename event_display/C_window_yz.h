#ifndef YZWINDOW_H
#define YZWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "C_view_yz.h"
#include "C_data.h"

// MAPT Framework
#include "DataManager.hh"
#include "Event.h"

class C_window_yz : public QMainWindow
{
    Q_OBJECT
public:
    explicit C_window_yz(QWidget *parent = 0, DataManager* d = 0);
    ~C_window_yz();

    bool IsOpen();
    bool close();

    void update();



private:

    QMenu *m_fileMenu;

    QAction* m_action;

    C_view_yz* m_center;

    bool m_isopen;

    DataManager* dataManager;



signals:

public slots:



};


#endif // YZWINDOW_H
