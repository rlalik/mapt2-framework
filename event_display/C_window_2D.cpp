#include "C_window_2D.h"

//
// Konstruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
C_window_2D::C_window_2D(C_view_2D::PLANE plane, QWidget *parent, DataManager* d) :
    QMainWindow(parent)
{
    // Fenster einrichten
    resize(450,450);
    setWindowTitle("Plane View");
    m_isopen = false;

    // Menu erstellen, Close einbauen
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_action = new QAction(tr("&Close"),this);
    m_action->setIconVisibleInMenu(true);
    m_fileMenu->addAction(m_action);


    dataManager = d;

    m_center = new C_view_2D(plane, 0, dataManager);
    setCentralWidget(m_center);

    // Close Slot einrichten
    connect(m_action, SIGNAL(triggered()),this, SLOT(close()));
}
// ----------------------------------------------------------------------------------------------------------------------------------
// Konstruktor ENDE


//
// IsOpen
// ----------------------------------------------------------------------------------------------------------------------------------
//
bool C_window_2D::IsOpen()
{
    return m_isopen;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// IsOpen ENDE


//
// close
// ----------------------------------------------------------------------------------------------------------------------------------
//
bool C_window_2D::close()
{
    m_isopen = false;
    return true;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// close ENDE


//
// update
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_window_2D::update()
{
    m_center->update();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// update ENDE


//
// Destruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
C_window_2D::~C_window_2D()
{
    delete m_fileMenu;
    delete m_action;
    delete m_center;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// Destruktor ENDE
