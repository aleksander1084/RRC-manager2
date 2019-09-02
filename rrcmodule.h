#ifndef RRCMODULE_H
#define RRCMODULE_H
#include <QObject>
#include <QDebug>
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
    void serialNumber(QString n_serialNumber);
    QString softwareVersion();
    void softwareVersion(QString n_softwareVersion);
    QString lastUpdate();
    void lastUpdate(int day, int month, int year);
    QString authenticity();
    bool checkDeviceAuthenticity(); //TODO: create
                                    //NOTE:command CHAU

    QStringList allSymbols();
    std::vector<ParameterList*> listModifiedParameters();

signals:
    void parameterChanged();

public slots:
    virtual void receiveParameterFromSerial(QStringList parameterSections);

protected:
    Parameter<uint8_t, 5> *mserialNumber;
    Parameter<uint8_t, 5> *msoftwareVersion;
    Parameter<uint8_t, 3> *mlastUpdate;
    Parameter<uint16_t, 1> *mauthenticity;
    Parameter<uint8_t, 1> *mRS485ID;
    Parameter<uint8_t, 3> *mchipIDSig;
    Parameter<uint8_t, 9> *mchipIDSN;
    std::vector<ParameterList *> paramneterList;
};

#endif // RRCMODULE_H
