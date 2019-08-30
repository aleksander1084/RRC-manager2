#include "rrcmodule.h"

RRCModule::RRCModule()
{
    mserialNumber =     new Parameter<uint8_t, 5>   ("Serial number", "SN", {0,0,0,0,0}, {0,0,0,0,0});
    msoftwareVersion =  new Parameter<uint8_t, 5>   ("Software version", "SV", {0,0,0,0,0}, {0,0,0,0,0});
    mlastUpdate =       new Parameter<uint8_t, 3>   ("Last update", "LU", {1,1,0}, {1,1,0});
    mauthenticity =     new Parameter<bool, 1>      ("Authenticity", "AU", {false}, {false});
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
    delete msoftwareVersion;
    delete mlastUpdate;
    delete mauthenticity;
    delete mRS485ID;
    delete mchipIDSig;
    delete mchipIDSN;
    //std::for_each(paramneterList.begin(), paramneterList.end(), [](ParameterList* param){delete param;});

}

QString RRCModule::serialNumber()
{
    QString mySerialNumber;
    for (int i = 0; i < int(mserialNumber->values.size()); ++i)
    {
        mySerialNumber += QString::number(int(mserialNumber->values[i]));
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
        mserialNumber->values[i] = uint8_t(sections.value(i).toInt());
    }
}

QString RRCModule::softwareVersion()
{
    QString mySoftwareVersion;
    for (int i = 0; i < int(msoftwareVersion->values.size()); ++i)
    {
        mySoftwareVersion += QString::number(int(msoftwareVersion->values[i]));
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
        msoftwareVersion->values[i] = uint8_t(sections.value(i).toInt());
    }
}

QString RRCModule::lastUpdate()
{
    QString myLastUpdate;
    for(int i = 0; i < int(mlastUpdate->values.size()); ++i)
    {
        if(i < int(mlastUpdate->values.size()) - 1)
        {
            QString section = QString::number(int(mlastUpdate->values[i]));
            myLastUpdate += QString::fromStdString(std::string(2 - section.length(), '0'));
            myLastUpdate += section;
            myLastUpdate += ".";
        }
        else
        {
            myLastUpdate += "2";
            QString year = QString::number(int(mlastUpdate->values[i]));
            myLastUpdate += QString::fromStdString(std::string(3 - year.length(), '0'));
            myLastUpdate += year;
        }
    }
    return myLastUpdate;
}

void RRCModule::lastUpdate(int day, int month, int year)
{
    mlastUpdate->values[0] = uint8_t(day);
    mlastUpdate->values[1] = uint8_t(month);
    mlastUpdate->values[2] = uint8_t(year % 2000);
}

QString RRCModule::authenticity()
{
    if(mauthenticity->values[mauthenticity->values.size() -1])
    {
        return "Module is authentic.";
    }
    else
    {
        return "Module authenticity test failed";
    }
}

