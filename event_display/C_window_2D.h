#ifndef C_WINDOW_2D_H
#define C_WINDOW_2D_H

#include <QMainWindow>
#include <QtGui>
#include "C_view_2D.h"
#include "C_data.h"

// MAPT Framework
#include "DataManager.hh"
#include "Event.h"

class QPushButton;
class QMenuBar;
class QMenu;
class QIcon;


class C_window_2D : public QMainWindow
{
    Q_OBJECT

public:
    explicit C_window_2D(C_view_2D::PLANE plane, QWidget *parent = 0, DataManager* d = 0);
    ~C_window_2D();

    bool IsOpen();
    bool close();
    void update();

private:
    QMenu *m_fileMenu;			// Menu
    QAction* m_action;			// Aktion im Menu
    C_view_2D* m_center;		// Ansicht
    bool m_isopen;			// Ist Fenster geoeffnet?
    DataManager* dataManager;			// Zeiger auf Datenklassen-Instanz
};

#endif // C_WINDOW_2D_H
