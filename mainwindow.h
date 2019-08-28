#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "testwidget.h"
#include "serialmonitor.h"
#include <QMenu>
#include "myserial.h"
#include "moduleselectdock.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TestWidget *testWidget;
    SerialMonitor *serialMonitor;
    ModuleSelectDock *mselectDock;
    QMenu *viewMenu;
    mySerial *serial;

    void topMenu();
    void setDocks();
    void returnSerialName();
    QMenu *createPopupMenu();
};

#endif // MAINWINDOW_H
