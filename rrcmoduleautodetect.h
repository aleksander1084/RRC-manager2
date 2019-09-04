#ifndef RRCMODULEAUTODETECT_H
#define RRCMODULEAUTODETECT_H

#include <QWidget>
#include <QTimer>
#include "myserial.h"
//TODO:Doxygen
class RRCModuleAutoDetect : public QWidget
{
    Q_OBJECT
public:
    explicit RRCModuleAutoDetect(mySerial *n_serialPort, QWidget *parent = nullptr);
    ~RRCModuleAutoDetect();

signals:
    void moduleAutomaticalyDetected();

public slots:
    void autoDetect();
    void timerStatus(bool status);
    void checkPrevousSerialDisconnected();

private:
    QTimer *mtimer;
    mySerial *mserialPort;
    std::vector<QStringList> macceptedForAutodetect = {
     /*Descriptions*/   {"CP210x"},
     /*Manufacturer*/   {"Silicon Labs"}
    };
    QString prevPortName;
};

#endif // RRCMODULEAUTODETECT_H
