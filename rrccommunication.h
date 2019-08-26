#ifndef RRCCOMMUNICATION_H
#define RRCCOMMUNICATION_H
#include "myserial.h"
#include "parameter.h"
#include "parameterlist.h"

class RRCCommunication
{
public:
//    struct Parameter{
//      QString name;
//      QString symbol;
//      int values[3];
//    };
    RRCCommunication(mySerial *n_serialPort);
    ~RRCCommunication();


    QString formatMessageToSendRequest(ParameterList *parameter);
    QString formatMessageToSendUpdate(ParameterList *parameter);
    //void readParametersList();
    //bool checkDeviceAuthenticity();
    void writeNewDevice();

//signals:
//    Parameter receivedNewParametr(QString message);

private:
    mySerial *serialPort;
    int deviceID;


};

#endif // RRCCOMMUNICATION_H
