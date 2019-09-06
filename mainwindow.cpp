#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testwidget.h"
#include <QtWidgets>
#include <QTabBar>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    topMenu();
    QTextEdit *myTextEdit = new QTextEdit();
    setCentralWidget(myTextEdit);

    setDocks();

    mautoDetect = new RRCModuleAutoDetect(serial, this);
    QObject::connect(mautoDetect, &RRCModuleAutoDetect::moduleAutomaticalyDetected, mselectDock, &ModuleSelectDock::checkAutomaticalyDetectedModule);
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
    delete testWidget;
    testWidget = nullptr;
    delete serialMonitor;
    serialMonitor = nullptr;
    delete mselectDock;
    mselectDock = nullptr;
    delete viewMenu;
    viewMenu = nullptr;
    if(serial != nullptr)
        if(serial->isOpen())
        {
            serial->disconnectSerialPort();
        }
    delete serial;
    serial = nullptr;
    if(communication->isDeclared){
        delete communication;
        communication = nullptr;
    }
    delete mautoDetect;
}

void MainWindow::topMenu()
{
    //QToolBar *fileToolBar   =   addToolBar(tr("File"));
    QMenu *fileMenu         =   menuBar()->addMenu(tr("&File"));

    //QAction *serialDebug = fileMenu->addAction(tr("&Debug Serial"), this, &MainWindow::returnSerialName);
    QAction *quitAct = fileMenu->addAction(tr("&Quit"), this, &QWidget::close);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    //QToolBar *editToolBar = addToolBar(tr("Edit"));
    QAction *undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last editing action"));
    //connect(undoAct, &QAction::triggered, this, &MainWindow::undo);
    editMenu->addAction(undoAct);

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"));




}

void MainWindow::setDocks()
{
    QDockWidget *dock = new QDockWidget(tr("Test"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    testWidget = new TestWidget(dock);
    dock->setWidget(testWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    QDockWidget *dock2 = new QDockWidget(tr("Serial Monitor"), this);
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    serialMonitor = new SerialMonitor(dock);
    dock2->setWidget(serialMonitor);
    //dock2->setTitleBarWidget(new QWidget(dock2));
    addDockWidget(Qt::BottomDockWidgetArea, dock2);
    viewMenu->addAction(dock2->toggleViewAction());
    serial = serialMonitor->currentSetting();
    communication = new RRCCommunication(serial);

    QDockWidget *dock3 = new QDockWidget("&Module select", this);
    dock3->setAllowedAreas(Qt::RightDockWidgetArea);
    mselectDock = new ModuleSelectDock(serial, communication);
    dock3->setWidget(mselectDock);
    addDockWidget(Qt::RightDockWidgetArea, dock3);
    //viewMenu->addAction(dock3->toggleViewAction());
    dock3->setTitleBarWidget(new QWidget(dock3));
    dock3->setFeatures(QDockWidget::NoDockWidgetFeatures);
    //dock3->setContextMenuPolicy(Qt::PreventContextMenu);

    QMainWindow::splitDockWidget(dock3, dock, Qt::Vertical);
    //qDebug() << "features " << dock3->features();
}

#ifndef QT_NO_MENU
/*!
    Returns a popup menu containing checkable entries for the toolbars and
    dock widgets present in the main window. If  there are no toolbars and
    dock widgets present, this function returns a null pointer.
    By default, this function is called by the main window when the user
    activates a context menu, typically by right-clicking on a toolbar or a dock
    widget.
    If you want to create a custom popup menu, reimplement this function and
    return a newly-created popup menu. Ownership of the popup menu is transferred
    to the caller.
    \sa addDockWidget(), addToolBar(), menuBar()
*/
QMenu *MainWindow::createPopupMenu()
{
    QMenu *menu = nullptr;
#ifndef QT_NO_DOCKWIDGET
    QList<QDockWidget *> dockwidgets = findChildren<QDockWidget *>();
    if (dockwidgets.size()) {
        menu = new QMenu(this);
        for (int i = 0; i < dockwidgets.size(); ++i) {
            QDockWidget *dockWidget = dockwidgets.at(i);
            if (dockWidget->parentWidget() == this
                && dockWidget->features() != QDockWidget::NoDockWidgetFeatures) {
                menu->addAction(dockwidgets.at(i)->toggleViewAction());
            }
        }
        menu->addSeparator();
    }
#endif // QT_NO_DOCKWIDGET
#ifndef QT_NO_TOOLBAR
    QList<QToolBar *> toolbars = findChildren<QToolBar *>();
    if (toolbars.size()) {
        if (!menu)
            menu = new QMenu(this);
        for (int i = 0; i < toolbars.size(); ++i) {
            QToolBar *toolBar = toolbars.at(i);
            if (toolBar->parentWidget() == this
                && ((unifiedTitleAndToolBarOnMac()
                        && toolBarArea(toolBar) == Qt::TopToolBarArea))) {
                menu->addAction(toolbars.at(i)->toggleViewAction());
            }
        }
    }
#endif
    return menu;
}
#endif // QT_NO_MENU


