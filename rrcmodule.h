#ifndef RRCMODULE_H
#define RRCMODULE_H
#include <QObject>
#include <QDebug>
#include "parameter.h"
/**
 * @brief The RRCModule class class defines basic parameters for all modules, base class for specified modules
 */
class RRCModule : public QObject
{

    Q_OBJECT

public:
    /**
     *@brief RRCModule basic class constructor
     */
    RRCModule();
    ~RRCModule();

    /**
     * @brief serialNumber methode returning module serial number
     */
    QString serialNumber();

    /**
     * @brief serialNumber method settin module Serial number
     * @param n_serialNumber Serial number in a string form with '/' betwen sections of the SN
     */
    void serialNumber(QString n_serialNumber);

    /**
     * @brief softwareVersion method returning software version
     */
    QString softwareVersion();

    /**
     * @brief softwareVersion method setting software version
     * @param n_softwareVersion string with new software version
     */
    void softwareVersion(QString n_softwareVersion);

    /**
     * @brief lastUpdate method returning last update date
     * @return
     */
    QString lastUpdate();

    /**
     * @brief lastUpdate function setting last update date
     * @param day
     * @param month
     * @param year
     */
    void lastUpdate(int day, int month, int year);

    /**
     * @brief authenticity method returning authenticity
     * @return
     */
    QString authenticity();

    /**
     * @brief checkDeviceAuthenticity method checking device authenticity
     * @return
     */
    bool checkDeviceAuthenticity(); //TODO: create
                                    //NOTE:command CHAU
    /**
     * @brief allSymbols function returning symbols of all parameters
     * @return
     */
    QStringList allSymbols();

    /**
     * @brief listModifiedParameters method returning vector of modified parameters
     * @return
     */
    std::vector<ParameterList*> listModifiedParameters();

signals:
    /**
     * @brief parameterChanged signal emited when parameter has new value set
     */
    void parameterChanged();

public slots:
    /**
     * @brief receiveParameterFromSerial definition of a virtual slot receiving message from the communication protocol
     * @param parameterSections
     */
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
