#ifndef MODULESELECTDOCK_H
#define MODULESELECTDOCK_H

#include <QWidget>
#include "myserial.h"
#include "moduleflasherwindow.h"
#include "rrccommunication.h"

namespace Ui {
class ModuleSelectDock;
}

class ModuleSelectDock : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleSelectDock(mySerial *n_serial, RRCCommunication *n_communication, QWidget *parent = nullptr);
    ~ModuleSelectDock();

private slots:
    void on_pushButtonFlasher_clicked();

private:
    Ui::ModuleSelectDock *ui;
    mySerial *serial;
    RRCCommunication *communication;
    QMainWindow *mWindow = nullptr;
};

#endif // MODULESELECTDOCK_H
