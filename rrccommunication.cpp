#include "rrccommunication.h"
#include <QDebug>
#include <sstream>
#include <iomanip>

RRCCommunication::RRCCommunication(mySerial *n_serialPort, RRCModule *n_module) : serialPort(n_serialPort), mmodule(n_module)
{
    QObject::connect(serialPort, &mySerial::newMessageReceived, this, &RRCCommunication::processNewMessage);
    QObject::connect(this, &RRCCommunication::receivedNewParametr, mmodule, &RRCModule::receiveParameterFromSerial);
    /*Debug() << "inicjalizacja RRCCommunication";
    qDebug() << "nazwa portu " << serialPort->name;*/
    isDeclared = true;

    QStringList unsignedInteagers = {QString::number(1),
                                     QString::number(2),
                                     QString::number(3),
                                     QString::number(4),
                                     QString::number(5),
                                     QString::number(6),
                                     QString::number(7),
                                     QString::number(10),
                                     QString::number(15),
                                     QString::number(20),
                                     QString::number(255),
                                     QString::number(1024)};
    qDebug() << "Inteagers:";
    codeUint(unsignedInteagers);

    QStringList bools = {QString::number(int(true)), QString::number(int(false)), QString::number(int(true)), QString::number(int(false))};
    qDebug() << "Bools:";
    codeBool(bools);

    QStringList floats = {QString::number(double(1.2)), QString::number(double(1.4)), QString::number(double(1.2)), QString::number(double(1.4))};
    qDebug() <<"Floats:";
    codeFloat(floats);


}

RRCCommunication::RRCCommunication(mySerial *n_serialPort) : RRCCommunication(n_serialPort, new RRCModule)
{
    isDeclared = true;
}

RRCCommunication::~RRCCommunication()
{
    qDebug() << "niszczę RRCCommunication";
    isDeclared = false;
    //QObject::disconnect(this, &RRCCommunication::receivedNewParametr, mmodule, &RRCModule::receiveParameterFromSerial);
}

void RRCCommunication::readDevice()
{
    QString readAllMessage = "<?|ALL>";
    serialPort->sendMessageToSerialPort(readAllMessage);
}

void RRCCommunication::updateDevice()
{
    std::vector<ParameterList *> parametersToUpdate = mmodule->listModifiedParameters();

    for (unsigned long long i = 0; i < parametersToUpdate.size(); ++i)
    {
        QStringList sections = parametersToUpdate.at(i)->readParameter();

        switch(sections.at(1).toInt())
        {
        case 0:
            sections = codeBool(sections);
            break;
        case 1:
            sections = codeUint(sections);
            break;
        case 2:
            sections = codeFloat(sections);
            break;
        }

        sendParameterToDevice(sections);
    }

    readDevice();
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
        //qDebug() << QString::number(uint8_t(temp));
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

QStringList RRCCommunication::codeBool(QStringList sections)
{
    QStringList response;
    response.push_back(sections.at(0));
    response.push_back(sections.at(1));
    for(int i = 2; i < sections.size(); ++i)
    {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << sections.at(i).toInt();
        response.push_back(QString::fromStdString(ss.str()));
        qDebug() << "hex value of " << sections.at(i) << " is " << QString::fromStdString(ss.str());
    }
    return response;
}

QStringList RRCCommunication::codeUint(QStringList sections)
{
    QStringList response;
    response.push_back(sections.at(0));
    response.push_back(sections.at(1));
    for(int i = 2; i < sections.size(); ++i)
    {
        std::stringstream ss;
        ss << std::setw(4) << std::setfill('0') << std::hex << sections.at(i).toInt();
        response.push_back(QString::fromStdString(ss.str()));
        qDebug() << "hex unsigned value of " << sections.at(i) << " is " << QString::fromStdString(ss.str());
    }
    return response;
}

QStringList RRCCommunication::codeFloat(QStringList sections)
{
    QStringList response;
    response.push_back(sections.at(0));
    response.push_back(sections.at(1));
//    for(int i = 2; i < sections.size(); ++i)
//    {
//        std::stringstream ss;
//        ss << std::fixed << std::hexfloat << sections.at(i).toFloat();
//        response.push_back(QString::fromStdString(ss.str()));
//        qDebug() << "hex float value of " << sections.at(i) << " is " << QString::fromStdString(ss.str());
//    }

    for(int i = 2; i < sections.size(); ++i)
        {
        unionForHexFloatConversion temp;
        temp.f = sections.at(i).toFloat();
        std::stringstream ss;
        ss << std::hex << temp.ul;
        response.push_back(QString::fromStdString(ss.str()));
        qDebug() << "hex float value of " << sections.at(i) << " is " << QString::fromStdString(ss.str());
        }

    return response;
}

void RRCCommunication::sendParameterToDevice(QStringList sections)
{
    QString message = "<!|";
    for (int i = 0; i < sections.size(); ++i)
    {
        message += sections.at(i);
        message += "|";
    }
    message += sections.at(sections.size()-1);
    message += ">";
    qDebug() << message;
    serialPort->sendMessageToSerialPort(message);
}

void RRCCommunication::processNewMessage(QString message)
{
    //qDebug() << "new message received: " << message;
    //test is message correct
    QStringRef plainMessage;
    bool test = false;
    if(message[0] == QChar('<')&& message[message.length()-1] == QChar('>'))
    {
        //qDebug() << "option 1";
        plainMessage = message.leftRef(message.length() - 1);
        test = true;
    }
    else if (message[0] == QChar('<') && message[message.length()-2] == QChar('>'))
    {
        //qDebug() << "option 2";
        plainMessage = message.leftRef(message.length() - 2);
        test = true;
    }

    if(test)
    {
        //qDebug() << "pre plain message: " << plainMessage;

        plainMessage = plainMessage.right(plainMessage.length()-1);

        qDebug() << "Plain message: " <<plainMessage;

        //cutting into sections
        message = plainMessage.toString();

        QStringList sections = message.split("|");

        //checking valType and converting to dec values
        int valTypeNum;
         std::istringstream(sections.at(1).toStdString()) >> std::hex >> valTypeNum;
         //qDebug() << "valTypeNum "<< valTypeNum;
        switch(valTypeNum){
        case 0 : sections = decodeBool(sections);
            break;
        case 1 : sections = decodeuint(sections);
            break;
        case 2 : sections = decodeFloat(sections);
        }

        emit receivedNewParametr(sections);
    }

}



