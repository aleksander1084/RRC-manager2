#ifndef RRCCOMMUNICATION_H
#define RRCCOMMUNICATION_H
#include "myserial.h"
#include "parameter.h"
#include "parameterlist.h"
#include "rrcmodule.h"
#include <QObject>

class RRCCommunication : public QObject
{
    Q_OBJECT
public:


    union unionForHexFloatConversion
    {
        unsigned long ul;
        float f;
    };

    RRCCommunication(mySerial *n_serialPort, RRCModule *n_module);
    RRCCommunication(mySerial *n_serialPort);
    ~RRCCommunication();


    QString formatMessageToSendRequest(ParameterList *parameter);
    QString formatMessageToSendUpdate(ParameterList *parameter);
    //bool checkDeviceAuthenticity();
    void writeNewDevice();

signals:
    void receivedNewParametr(QStringList parameterSections);

private:
    mySerial *serialPort;
    RRCModule *mmodule;

    QStringList decodeBool(QStringList sections);
    QStringList decodeuint(QStringList sections);
    QStringList decodeFloat(QStringList sections);


private slots:
    void processNewMessage(QString message);


};

#endif // RRCCOMMUNICATION_H
