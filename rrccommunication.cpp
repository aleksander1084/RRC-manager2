#include "rrccommunication.h"
#include <QDebug>
#include <sstream>

RRCCommunication::RRCCommunication(mySerial *n_serialPort, RRCModule *n_module) : serialPort(n_serialPort), mmodule(n_module)
{
    QObject::connect(serialPort, &mySerial::newMessageReceived, this, &RRCCommunication::processNewMessage);
    /*Debug() << "inicjalizacja RRCCommunication";
    qDebug() << "nazwa portu " << serialPort->name;*/
}

RRCCommunication::RRCCommunication(mySerial *n_serialPort) : RRCCommunication(n_serialPort, new RRCModule)
{
}

RRCCommunication::~RRCCommunication()
{
    qDebug() << "niszczę RRCCommunication";
}

QStringList RRCCommunication::decodeBool(QStringList sections)
{
    return sections;
}

QStringList RRCCommunication::decodeuint(QStringList sections)
{
    QStringList response = sections;
    for(int i = 2; i < sections.size(); ++i)
    {
        int temp;
        std::istringstream(sections.at(i).toStdString()) >> std::hex >> temp;
        qDebug() << QString::number(uint8_t(temp));
        response.replace(i, QString::number(uint8_t(temp)));
        //qDebug() << "test crazy thing" << QString::number(temp);
    }

    return response;
}

QStringList RRCCommunication::decodeFloat(QStringList sections)
{
    QStringList response = sections;

    for(int i = 2; i < sections.size(); ++i)
    {
          unionForHexFloatConversion temp;
              std::string str = sections.at(i).toStdString();
              std::stringstream ss(str);
              ss >> std::hex >> temp.ul;
              float temp2 = temp.f;
              response.replace(i, QString::number(double(temp2), 'f', 1));
          //qDebug() << "test crazy thing cos" << QString::number(double(f), 'f', 1);
              //qDebug() << response.at(i);

    }
    return response;
}

void RRCCommunication::processNewMessage(QString message)
{
    //qDebug() << "new message received: " << message;
    //test is message correct
    QStringRef plainMessage;
    if(message[0] == QChar('<')&& message[message.length()-1] == QChar('>'))
    {
        //qDebug() << "option 1";
        plainMessage = message.leftRef(message.length() - 1);
    }
    else if (message[0] == QChar('<') && message[message.length()-2] == QChar('>'))
    {
        //qDebug() << "option 2";
        plainMessage = message.leftRef(message.length() - 2);
    }
    //qDebug() << "pre plain message: " << plainMessage;

    plainMessage = plainMessage.right(plainMessage.length()-1);

    qDebug() << "Plain message: " <<plainMessage;

    //cutting into sections
    message = plainMessage.toString();

    QStringList sections = message.split("|");

    //checking valType and converting to dec values
    int valTypeNum;
     std::istringstream(sections.at(1).toStdString()) >> std::hex >> valTypeNum;
     qDebug() << "valTypeNum "<< valTypeNum;
    switch(valTypeNum){
    case 0 : sections = decodeBool(sections);
        break;
    case 1 : sections = decodeuint(sections);
        break;
    case 2 : sections = decodeFloat(sections);
    }

    //convert hex values to dec
    for(int i = 2; i < sections.size(); ++i)
    {
        qDebug() << "test crazy thing" << QString::number(i) << " " << sections.at(i);
    }
    emit receivedNewParametr(sections);
}


