#include "C_mainwindow.h"

#include "MMAPTManager.h"
#include "MDetectorManager.h"
#include "MGeantTrack.h"
#include "MGeantFibersRaw.h"

#include "MFibersDetector.h"

#include <QtGui>

C_MainWindow::C_MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Fenster einstellen
    resize(1024,25);
    move(0,0);
    setWindowTitle("Live Event Display");

    // load data
    dataManager = MMAPTManager::instance();
    dataManager->setSimulation(true);

    // initialize detectors
    MDetectorManager * detm = MDetectorManager::instance();
    detm->addDetector(new MFibersDetector("Fibers"));
    detm->initCategories();

    m_winXZ = new C_window_2D(C_view_2D::XY, dataManager);
    m_winXZ->move(this->pos()+QPoint(0,140));
    m_winXZ->setWindowTitle("X-Z plane");
    m_winXZ->show();

    m_winYZ = new C_window_2D(C_view_2D::ZY, dataManager);
    m_winYZ->move(this->pos()+QPoint(450,140));
    m_winYZ->setWindowTitle("Y-Z plane");
    m_winYZ->show();

    m_win3D = new C_window_3D(dataManager);
    m_win3D->move(this->pos()+QPoint(900,140));
    m_win3D->show();

    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    m_next = new QPushButton("&next");
    m_next->setEnabled(false);

    m_last = new QPushButton("&previous");
    m_last->setEnabled(false);

    // Layout einrichten
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);

    layout->addWidget(m_last);
    layout->addWidget(m_next);

    layout->addWidget(bottomFiller);

    QHBoxLayout* whole_layout = new QHBoxLayout;
    QHBoxLayout* under_layout = new QHBoxLayout;
    QHBoxLayout* spin_layout = new QHBoxLayout;

    m_Label2 = new QLabel("eventnumber: 0");

    under_layout->addWidget(m_Label2);

    whole_layout->addLayout(under_layout,0.3);
    whole_layout->addLayout(layout,0.3);
    whole_layout->addLayout(spin_layout,0.3);

    widget->setLayout(whole_layout);

    // Menu einrichten
    fileMenu2 = menuBar()->addMenu(tr("&File"));
    fileMenu = menuBar()->addMenu(tr("&Windows"));

    open = new QAction(tr("&Open"),this);
    fileMenu2->addAction(open);

    openEvent = new QAction(tr("&Open Event"),this);
    fileMenu2->addAction(openEvent);

    view3D = new QAction(tr("&3D representation"),this);
    fileMenu->addAction(view3D);

    yzView = new QAction(tr("&z y View"),this);
    fileMenu->addAction(yzView);

    xzView = new QAction(tr("&x y View"),this);
    fileMenu->addAction(xzView);

    // Slots einrichten
    connect(xzView, SIGNAL(triggered()), SLOT(OpenXZ()));
    connect(yzView, SIGNAL(triggered()), SLOT(OpenYZ()));
    connect(view3D, SIGNAL(triggered()), SLOT(Open3D()));

    connect(open, SIGNAL(triggered()), SLOT(Open()));
    connect(openEvent, SIGNAL(triggered()), SLOT(OpenEvent()));

    connect(m_next, SIGNAL(clicked()), SLOT(next()));
    connect(m_last, SIGNAL(clicked()), SLOT(last()));
}

void C_MainWindow::openFile(const QString & fn)
{
    dataManager->setInputFileName(fn.toStdString());
    if (dataManager->open())
    {
        dataManager->openCategory(MCategory::CatGeantTrack);
        dataManager->openCategory(MCategory::CatGeantFibersRaw);
        dataManager->getEntry(0);

//         catGeantTrack = dataManager->getCategory(MCategory::CatGeantTrack);
//         catGeantFibersRaw = dataManager->getCategory(MCategory::CatGeantFibersRaw);

        update();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("The file cannot be opened. May this file contains a unknown data format.");
        msgBox.exec();
    }
}

void C_MainWindow::Open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Load Root Tree"), "", tr("root files (*.root)"));

    std::cout << fileName.toStdString() << "\n";
    openFile(fileName);
}

void C_MainWindow::OpenEvent()
{
    QInputDialog *input = new QInputDialog();
    bool ok;

    int numb;

    numb = input->getInteger(this,"Open Eventnumber", "Eventnumber",dataManager->getCurrentEntryNumber(),0,dataManager->getNumberOfEntries(),1,&ok,0);

    dataManager->getEntry(numb);

    delete input;

    update();
}

void C_MainWindow::OpenXZ()
{
    if (!m_winXZ->IsOpen())
        m_winXZ->show();
}

void C_MainWindow::OpenYZ()
{
    if (!m_winYZ->IsOpen())
        m_winYZ->show();
}

void C_MainWindow::Open3D()
{
    m_win3D->show();
}

void C_MainWindow::next()
{
    // next in event in tree
    int n = dataManager->getCurrentEntryNumber();
    if (n+1<= dataManager->getNumberOfEntries()) {
        dataManager->getEntry(n+1);
    }

    update();
}

void C_MainWindow::last()
{
    // next in event in tree
    int n = dataManager->getCurrentEntryNumber();
    if (n-1 >= 0) {
        dataManager->getEntry(n-1);
    }

    update();
}

void C_MainWindow::update()
{
    // update an window-Klassen weitergeben
    m_win3D->update();
    m_winYZ->update();
    m_winXZ->update();

    // Ansicht und Informationen im Hauptfenster aktualisieren

    // Aktuelle Eventnummer aktualisieren und ausgeben
    QString s = "eventnumber ";
    s = s + QString::number(dataManager->getCurrentEntryNumber());
    m_Label2->setText(s);

    int n = dataManager->getCurrentEntryNumber();

    if (n+1<= dataManager->getNumberOfEntries()) {
        m_next->setEnabled(true);
    }
    else {
        m_next->setEnabled(false);
    }

    if (n-1>= 0) {
        m_last->setEnabled(true);
    }
    else {
        m_last->setEnabled(false);
    }
}

C_MainWindow::~C_MainWindow()
{
    delete m_next;
    delete m_last;

    delete m_Label2;

    delete fileMenu;
    delete fileMenu2;

    delete xzView;
    delete yzView;
    delete view3D;
    delete open;

}
