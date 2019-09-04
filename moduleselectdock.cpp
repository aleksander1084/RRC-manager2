#include "moduleselectdock.h"
#include "ui_moduleselectdock.h"
#include <QMessageBox>
#include <QTimer>


ModuleSelectDock::ModuleSelectDock(mySerial *n_serial, RRCCommunication *n_communication, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleSelectDock),
    serial(n_serial),
    communication(n_communication)
{
    ui->setupUi(this);
}

ModuleSelectDock::~ModuleSelectDock()
{
    delete ui;
    ui = nullptr;
}

void ModuleSelectDock::on_pushButtonFlasher_clicked()
{
    mWindow = new ModuleFlasherWindow(serial, communication, this);
    QObject::connect(mWindow, &QDialog::rejected, this, &ModuleSelectDock::mWindowWasRejected);
    mWindow->setAttribute(Qt::WA_DeleteOnClose);
    mWindow->show();
}

void ModuleSelectDock::checkAutomaticalyDetectedModuleSN(QStringList sections)
{
    if(sections.at(0) == "SN"){
        QObject::disconnect(communication, &RRCCommunication::receivedNewParametr, this, &ModuleSelectDock::checkAutomaticalyDetectedModuleSN);
        automaticConnectionsTries = 0;
        if(sections.at(2) == "11")//flasher
        {
            on_pushButtonFlasher_clicked();
        }
        else if(sections.at(2) == "12")//MW
        {
            //qDebug() << "7c";
            on_pushButtonMW_clicked();
            //qDebug() << "7d";
        }
        else if(sections.at(2) == "13")//Lidar
        {
            //qDebug() << "7e";
            on_pushButtonLidar_clicked();
            //qDebug() << "7f";
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Automaticaly connected module not recognised" + sections.at(2));
            msgBox.exec();
            automaticConnectionsTries = 0;
        }
    }
    else if(automaticConnectionsTries >=2)
    {
        QObject::disconnect(communication, &RRCCommunication::receivedNewParametr, this, &ModuleSelectDock::checkAutomaticalyDetectedModuleSN);
        automaticConnectionsTries = 0;
    }
    else {
        QEventLoop loop;
        QTimer::singleShot(1500, &loop, &QEventLoop::quit);
        loop.exec();
        communication->checkModuleSN();
        automaticConnectionsTries++;
    }
}

void ModuleSelectDock::mWindowWasRejected()
{
    mWindow = nullptr;
}

void ModuleSelectDock::checkAutomaticalyDetectedModule()
{
    //qDebug() << "1";
    delete communication;
    //qDebug() << "2";
    communication = new RRCCommunication(serial);
    //qDebug() << "3";
    QObject::connect(communication, &RRCCommunication::receivedNewParametr, this, &ModuleSelectDock::checkAutomaticalyDetectedModuleSN);
    //qDebug() << "4";
    communication->checkModuleSN();
    //qDebug() << "5";
}

void ModuleSelectDock::on_pushButtonMW_clicked()
{

}

void ModuleSelectDock::on_pushButtonLidar_clicked()
{

}
