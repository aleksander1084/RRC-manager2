#ifndef RRCMODULE_H
#define RRCMODULE_H
#include <QObject>
#include "parameter.h"
/**
 * @brief The RRCModule class class defines basic parameters for all modules
 */
class RRCModule : public QObject
{

    Q_OBJECT

public:
    RRCModule();
    ~RRCModule();
    QString serialNumber();
    QString softwareVersion();
    QString lastUpdate();
    bool checkDeviceAuthenticity();
    void readParameter();
    void setParameter();

private:
    Parameter<uint8_t, 5> *mserialNumber;
    Parameter<uint8_t, 5> *msoftwareVersion;
    Parameter<uint8_t, 3> *mlastUpdate;
    Parameter<bool, 1> *mauthenticity;
    Parameter<uint8_t, 1> *mRS485ID;
    Parameter<uint8_t, 1> *mchipID;
    std::vector<ParameterList *> paramneterList;
};

#endif // RRCMODULE_H
