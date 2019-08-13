#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testwidget.h"
#include <QtWidgets>
#include <QTabBar>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    topMenu();
    QTextEdit *myTextEdit = new QTextEdit();
    setCentralWidget(myTextEdit);
    setDocks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::topMenu()
{
    //QToolBar *fileToolBar   =   addToolBar(tr("File"));
    QMenu *fileMenu         =   menuBar()->addMenu(tr("&File"));

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
    addDockWidget(Qt::BottomDockWidgetArea, dock2);
    viewMenu->addAction(dock2->toggleViewAction());
}


