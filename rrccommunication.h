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
    bool isDeclared;


    union unionForHexFloatConversion
    {
        unsigned long ul;
        float f;
    };

    RRCCommunication(mySerial *n_serialPort, RRCModule *n_module);
    RRCCommunication(mySerial *n_serialPort);
    ~RRCCommunication();

    void readDevice();//TODO: create
    void writeNewDevice();//TODO: create
    void updateDevice();

signals:
    void receivedNewParametr(QStringList parameterSections);

private:
    mySerial *serialPort;
    RRCModule *mmodule;
    QStringList decodeBool(QStringList sections);
    QStringList decodeuint(QStringList sections);
    QStringList decodeFloat(QStringList sections);

    QStringList codeBool(QStringList sections);//TODO:create
    QStringList codeUint(QStringList sections);//TODO:create
    QStringList codeFloat(QStringList sections);//TODO:create
    void sendParameterToDevice(QStringList sections);

private slots:
    void processNewMessage(QString message);




};

#endif // RRCCOMMUNICATION_H
