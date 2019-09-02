#include "rrcmodule.h"

RRCModule::RRCModule()
{
    mserialNumber =     new Parameter<uint8_t, 5>   ("Serial number", "SN", {0,0,0,0,0}, {0,0,0,0,0});
    msoftwareVersion =  new Parameter<uint8_t, 5>   ("Software version", "SV", {0,0,0,0,0}, {0,0,0,0,0});
    mlastUpdate =       new Parameter<uint8_t, 3>   ("Last update", "LU", {1,1,0}, {1,1,0});
    mauthenticity =     new Parameter<uint16_t, 1>      ("Authenticity", "AU", {0}, {0});
    mRS485ID =          new Parameter<uint8_t, 1>   ("RS485 identifier", "RS4", {1}, {1});
    mchipIDSig =        new Parameter<uint8_t, 3>   ("Chip signature", "CHID", {0,0,0}, {0,0,0});
    mchipIDSN =         new Parameter<uint8_t, 9>   ("Chip serial number", "CHSN", {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0});

    paramneterList.push_back(mserialNumber);
    paramneterList.push_back(msoftwareVersion);
    paramneterList.push_back(mlastUpdate);
    paramneterList.push_back(mauthenticity);
    paramneterList.push_back(mRS485ID);
    paramneterList.push_back(mchipIDSig);
    paramneterList.push_back(mchipIDSN);
}

RRCModule::~RRCModule()
{
    delete mserialNumber;
    mserialNumber = nullptr;
    delete msoftwareVersion;
    msoftwareVersion = nullptr;
    delete mlastUpdate;
    mlastUpdate = nullptr;
    delete mauthenticity;
    mauthenticity = nullptr;
    delete mRS485ID;
    mRS485ID = nullptr;
    delete mchipIDSig;
    mchipIDSig = nullptr;
    delete mchipIDSN;
    mchipIDSN = nullptr;
    //std::for_each(paramneterList.begin(), paramneterList.end(), [](ParameterList* param){delete param;});

}

QString RRCModule::serialNumber()
{
    QString mySerialNumber;
    for (int i = 0; i < int(mserialNumber->values.size()); ++i)
    {
        mySerialNumber += QString::number(int(mserialNumber->values[unsigned(i)]));
        if(i < int(mserialNumber->values.size()) - 1)
        {
            mySerialNumber += "/";
        }
    }
    return mySerialNumber;
}

void RRCModule::serialNumber(QString n_serialNumber)
{
    QStringList sections = n_serialNumber.split("/");
    for (int i = 0; i < sections.length(); ++i)
    {
        if(mserialNumber->values[unsigned(i)] != uint8_t(sections.value(i).toInt()))
        {
            mserialNumber->values[unsigned(i)] = uint8_t(sections.value(i).toInt());
            mserialNumber->myChanged(true);
        }

    }
}

QString RRCModule::softwareVersion()
{
    QString mySoftwareVersion;
    for (int i = 0; i < int(msoftwareVersion->values.size()); ++i)
    {
        mySoftwareVersion += QString::number(int(msoftwareVersion->values[unsigned(i)]));
        if(i < int(msoftwareVersion->values.size()) - 1)
        {
            mySoftwareVersion += "/";
        }
    }
    return mySoftwareVersion;
}

void RRCModule::softwareVersion(QString n_softwareVersion)
{
    QStringList sections = n_softwareVersion.split("/");
    for (int i = 0; i < sections.length(); ++i)
    {
        if(msoftwareVersion->values[unsigned(i)] != uint8_t(sections.value(i).toInt()))
        {
            msoftwareVersion->values[unsigned(i)] = uint8_t(sections.value(i).toInt());
            msoftwareVersion->myChanged(true);
        }

    }
}

QString RRCModule::lastUpdate()
{
    QString myLastUpdate;
    for(int i = 0; i < int(mlastUpdate->values.size()); ++i)
    {
        if(i < int(mlastUpdate->values.size()) - 1)
        {
            QString section = QString::number(int(mlastUpdate->values[unsigned(i)]));
            myLastUpdate += QString::fromStdString(std::string(2 - section.length(), '0'));
            myLastUpdate += section;
            myLastUpdate += ".";
        }
        else
        {
            myLastUpdate += "2";
            QString year = QString::number(int(mlastUpdate->values[unsigned(i)]));
            myLastUpdate += QString::fromStdString(std::string(3 - year.length(), '0'));
            myLastUpdate += year;
        }
    }
    return myLastUpdate;
}

void RRCModule::lastUpdate(int day, int month, int year)
{
    if(uint8_t(day) != mlastUpdate->values[0]
            || uint8_t(month) != mlastUpdate->values[1]
            || uint8_t(year) != mlastUpdate->values[2])
    {
        mlastUpdate->values[0] = uint8_t(day);
        mlastUpdate->values[1] = uint8_t(month);
        mlastUpdate->values[2] = uint8_t(year % 2000);
        mlastUpdate->myChanged(true);
    }
}

QString RRCModule::authenticity()
{
    if(mauthenticity->values[mauthenticity->values.size() -1] != 0)
    {
        return "Module is authentic.";
    }
    else
    {
        return "Module authenticity test failed";
    }
}

QStringList RRCModule::allSymbols()
{
    QStringList symbolsSet;

    for(unsigned long long i = 0; i < paramneterList.size(); ++i)
    {
        symbolsSet.push_back(paramneterList.at(i)->mySymbol());
    }
    return symbolsSet;
}

std::vector<ParameterList*> RRCModule::listModifiedParameters()
{
    std::vector<ParameterList*> response;

    for (unsigned long long i = 0; i < paramneterList.size();++i)
    {
        if(paramneterList.at(i)->myChanged())
        {
            response.push_back(paramneterList.at(i));
            paramneterList.at(i)->myChanged(false);
        }
    }
    return response;
}

void RRCModule::receiveParameterFromSerial(QStringList parameterSections)
{
//    if(parameterSections.at(0) == "SN")
//    {
//        QString serialNumberString;
//        for (int i = 1; i<5;++i)
//        {
//           serialNumberString += parameterSections.at(i) + "/";
//        }
//        serialNumberString += parameterSections.at(5);
//        serialNumber(serialNumberString);
//        return;
//    }
//    else if (parameterSections.at(0) == "SV")
//    {

//    }
    qDebug() << "receiveParameterFromSerial";
    for(unsigned long long i = 0; i < paramneterList.size(); ++i)
    {
        //qDebug() << parameterSections.at(0)
        if(parameterSections.at(0) == paramneterList.at(i)->mySymbol())
        {
            qDebug() << "receiveParameterFromSerial: found parameter: " << paramneterList.at(i)->myName();
            paramneterList.at(i)->setParameter(parameterSections);
        }
    }

    emit parameterChanged();
}

