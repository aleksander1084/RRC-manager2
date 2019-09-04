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

public slots:
    void checkAutomaticalyDetectedModule();

private slots:
    void on_pushButtonFlasher_clicked();
    void checkAutomaticalyDetectedModuleSN(QStringList sections);
    void mWindowWasRejected();



    void on_pushButtonMW_clicked();

    void on_pushButtonLidar_clicked();

private:
    Ui::ModuleSelectDock *ui;
    mySerial *serial;
    RRCCommunication *communication;
    QDialog *mWindow = nullptr;
    int automaticConnectionsTries = 0;
};

#endif // MODULESELECTDOCK_H
