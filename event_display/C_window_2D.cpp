#include "C_window_2D.h"

C_window_2D::C_window_2D(C_view_2D::PLANE plane, MMAPTManager* d, QWidget *parent) :
    dataManager(d), QMainWindow(parent)
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

    m_center = new C_view_2D(plane, dataManager);
    setCentralWidget(m_center);

    // Close Slot einrichten
    connect(m_action, SIGNAL(triggered()),this, SLOT(close()));
}

bool C_window_2D::IsOpen()
{
    return m_isopen;
}

bool C_window_2D::close()
{
    m_isopen = false;
    return true;
}

void C_window_2D::update()
{
    m_center->update();
}

C_window_2D::~C_window_2D()
{
    delete m_fileMenu;
    delete m_action;
    delete m_center;
}
