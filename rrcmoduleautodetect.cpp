#include "rrcmoduleautodetect.h"


RRCModuleAutoDetect::RRCModuleAutoDetect(mySerial *n_serialPort, QWidget *parent) : QWidget(parent)
{
    mserialPort = n_serialPort;
    mtimer = new QTimer(this);
            QObject::connect(mtimer, &QTimer::timeout, this, &RRCModuleAutoDetect::autoDetect);
            QObject::connect(mserialPort, &mySerial::serialConnectionStuatusSignal, this, &RRCModuleAutoDetect::timerStatus);
            mtimer->start(1000); //time specified in ms
}

RRCModuleAutoDetect::~RRCModuleAutoDetect()
{
    delete mtimer;
}

void RRCModuleAutoDetect::autoDetect()
{
    std::vector<QSerialPortInfo> acceptedPorts;
    std::vector<int> acceptedPortsIndexes;
    //qDebug() << "Auto Detect test";
    const auto infos = QSerialPortInfo::availablePorts();
    for (int j = 0; j < infos.size(); ++j) {
        for(int i = 0; i < macceptedForAutodetect.at(0).size(); ++i)
        {
            if(infos.at(j).description().contains(macceptedForAutodetect.at(0).at(i)) && infos.at(j).manufacturer().contains(macceptedForAutodetect.at(1).at(i))){
               acceptedPorts.push_back(infos.at(j));
               acceptedPortsIndexes.push_back(j);
            }
        }

    }
    if(acceptedPorts.size() == 1)
    {
        //qDebug() << "connecting automaticaly to " << acceptedPorts.at(0).portName();
        emit mserialPort->searchSignal();
        mserialPort->setName(acceptedPorts.at(0).portName());
        emit mserialPort->serialIndexChanged(acceptedPortsIndexes.at(0));
        emit mserialPort->settingsChangedSignal();
        mserialPort->connectSerialPort();
        prevPortName = acceptedPorts.at(0).portName();
        //qDebug() << "emites detection of new module";
        emit moduleAutomaticalyDetected();
    }


}

void RRCModuleAutoDetect::timerStatus(bool status)
{
    if(status){
        mtimer->stop();
    }
    else {
        QObject::disconnect(mtimer, &QTimer::timeout, this, &RRCModuleAutoDetect::autoDetect);
        QObject::connect(mtimer, &QTimer::timeout, this, &RRCModuleAutoDetect::checkPrevousSerialDisconnected);
        mtimer->start(1000);
    }
}

void RRCModuleAutoDetect::checkPrevousSerialDisconnected()
{
    bool serialPortStillAvaliable = false;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        if(info.portName() == prevPortName)
        {
            serialPortStillAvaliable = true;
        }
    }
    if(!serialPortStillAvaliable)
    {
        QObject::disconnect(mtimer, &QTimer::timeout, this, &RRCModuleAutoDetect::checkPrevousSerialDisconnected);
        QObject::connect(mtimer, &QTimer::timeout, this, &RRCModuleAutoDetect::autoDetect);
        prevPortName = "0";
    }
}
