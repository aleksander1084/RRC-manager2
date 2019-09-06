#ifndef RRCCOMMUNICATION_H
#define RRCCOMMUNICATION_H
#include "myserial.h"
#include "parameter.h"
#include "parameterlist.h"
#include "rrcmodule.h"
#include <QObject>
/**
 * @brief The RRCCommunication class class definig message processing standard for RRC modules
 */
class RRCCommunication : public QObject
{
    Q_OBJECT
public:
    bool isDeclared; /**< flag used for checking can object be deleted */

    /**
     * @brief checkModuleSN method called when there is a need to check SN of a connected module
     */
    void checkModuleSN();

    /**
     * @brief The unionForHexFloatConversion union used for conversion of the float value to the IEEE 754 hex standard
     */
    union unionForHexFloatConversion
    {
        unsigned long ul;
        float f;
    };

    /**
     * @brief RRCCommunication constructo of the class
     * @param n_serialPort pointer to the used serial port, that will receive and transmit data for this module
     * @param n_module pointer to the module representation that uses this communication standard
     */
    RRCCommunication(mySerial *n_serialPort, RRCModule *n_module);
    /**
     * @brief RRCCommunication overload of the class class constructor that uses new general RRCModule to identify new connected module
     */
    RRCCommunication(mySerial *n_serialPort);
    ~RRCCommunication();

    /**
     * @brief readDevice method responsible for reading connected module
     */
    void readDevice();

    /**
     * @brief writeNewDevice method responsible for writing memory of a new module
     */
    void writeNewDevice();//TODO: create

    /**
     * @brief updateDevice method called to update parameters of a module to the set ones
     */
    void updateDevice();

signals:
    /**
     * @brief receivedNewParametr signal emited when new received parameter is processed
     * @param parameterSections QString List of all decoded message parameters
     */
    void receivedNewParametr(QStringList parameterSections);

private:
    mySerial *serialPort; /**<pointer to the actually used serial port */
    RRCModule *mmodule; /**<pointer to the module using this communication method*/

    /**
     * @brief decodeBool method responsible for decodding bool type parameter
     * @param sections parsed received message
     * @return list containing sections of a decoded message
     */
    QStringList decodeBool(QStringList sections);

    /**
     * @brief decodeuint method responsible for decodding uint type parameter
     * @param sections parsed received message
     * @return list containing sections of a decoded message
     */
    QStringList decodeuint(QStringList sections);

    /**
     * @brief decodeFloat method responsible for decodding float type parameter
     * @param sections parsed received message
     * @return list containing sections of a decoded message
     */
    QStringList decodeFloat(QStringList sections);

    /**
     * @brief codeBool method called for codding bool type parameter
     * @param sections message to code
     * @return codded message
     */
    QStringList codeBool(QStringList sections);

    /**
     * @brief codeUint method called for codding uint type parameter
     * @param sections message to code
     * @return codded message
     */
    QStringList codeUint(QStringList sections);

    /**
     * @brief codeFloat method called for codding float type parameter
     * @param sections message to code
     * @return codded message
     */
    QStringList codeFloat(QStringList sections);

    /**
     * @brief sendParameterToDevice method called to update parameter in the module
     * @param sections codded message
     */
    void sendParameterToDevice(QStringList sections);

private slots:
    /**
     * @brief processNewMessage slot called when new message is received over serial port, parsing message
     * @param message recceived message
     */
    void processNewMessage(QString message);
};

#endif // RRCCOMMUNICATION_H
