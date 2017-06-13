#ifndef XZWINDOW_H
#define XZWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "C_view_xz.h"
#include "C_data.h"

// MAPT Framework
#include "DataManager.hh"
#include "Event.h"

class QPushButton;
class QMenuBar;
class QMenu;
class QIcon;


class C_window_xz : public QMainWindow
{
    Q_OBJECT

public:
    explicit C_window_xz(QWidget *parent = 0, DataManager* d = 0);
    ~C_window_xz();

    bool IsOpen();
    bool close();

    void update();



private:

    QMenu *m_fileMenu;			// Menu

    QAction* m_action;			// Aktion im Menu

    C_view_xz* m_center;		// Ansicht

    bool m_isopen;			// Ist Fenster geoeffnet?

    DataManager* dataManager;			// Zeiger auf Datenklassen-Instanz



signals:

public slots:



};

#endif // XZWINDOW_H
