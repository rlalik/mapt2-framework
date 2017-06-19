#ifndef MAINWINDOW_H
#define MAINWINDOW_H




#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include "C_window_3D.h"
#include "C_window_2D.h"

// MAPT Framework
#include "DataManager.hh"
#include "Event.h"


class QPushButton;
class QMenuBar;
class QMenu;
class QIcon;

class C_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    C_MainWindow(QWidget *parent = 0);
    ~C_MainWindow();
    void update();
    C_dat* getdaten();

private:
    DataManager* dataManager;
    Event* event;

    QPushButton* m_next;
    QPushButton* m_last;

    QLabel *m_Label2;

    QMenu *fileMenu;
    QMenu *fileMenu2;

    QAction* xzView;
    QAction* yzView;
    QAction* view3D;
    QAction* open;
    QAction* openEvent;

    C_window_2D* m_winXZ;
    C_window_2D* m_winYZ;
    C_window_3D* m_win3D;

private slots:
    void OpenXZ ();
    void OpenYZ ();
    void Open3D ();
    void Open();
    void OpenEvent();
    void next();
    void last();
};

#endif // MAINWINDOW_H
