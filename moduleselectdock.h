#ifndef MODULESELECTDOCK_H
#define MODULESELECTDOCK_H

#include <QWidget>
#include "myserial.h"
#include "moduleflasherwindow.h"

namespace Ui {
class ModuleSelectDock;
}

class ModuleSelectDock : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleSelectDock(mySerial *n_serial, QWidget *parent = nullptr);
    ~ModuleSelectDock();

private slots:
    void on_pushButtonFlasher_clicked();

private:
    Ui::ModuleSelectDock *ui;
    mySerial *serial;
    QMainWindow *mWindow = nullptr;
};

#endif // MODULESELECTDOCK_H
