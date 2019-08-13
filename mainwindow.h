#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "testwidget.h"
#include "serialmonitor.h"
#include <QMenu>

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
    QMenu *viewMenu;

    void topMenu();
    void setDocks();
};

#endif // MAINWINDOW_H
