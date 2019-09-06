#ifndef RRCMODULEAUTODETECT_H
#define RRCMODULEAUTODETECT_H

#include <QWidget>
#include <QTimer>
#include "myserial.h"
/**
 * @brief The RRCModuleAutoDetect class responsible for autodetection of a connected module
 * @author Aleksander Felisiak
 * @date $Date: 2019/08/17 12:22:00 $
 *
 * Contact: olek.felisiak@gmail.com
 *
 * Created on: Saturday Aug 17th 2019
 */
class RRCModuleAutoDetect : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief RRCModuleAutoDetect class constructor
     * @param n_serialPort pointer to the active serial port
     * @param parent pointer to the calling object, QT Standard
     */
    explicit RRCModuleAutoDetect(mySerial *n_serialPort, QWidget *parent = nullptr);
    ~RRCModuleAutoDetect();

signals:
    /**
     * @brief moduleAutomaticalyDetected signal emited when new USB port from the list of detectable is detected
     */
    void moduleAutomaticalyDetected();

public slots:
    /**
     * @brief autoDetect main method of the autodetection, called every 1s with a timer
     */
    void autoDetect();

    /**
     * @brief timerStatus methode responsible for diabling/enabling timer that is calling test
     * @param status
     */
    void timerStatus(bool status);

    /**
     * @brief checkPrevousSerialDisconnected slot called by a timer when autodetection is off and serial port is disconnected to check was a serial port adapter disconnected
     */
    void checkPrevousSerialDisconnected();

private:
    QTimer *mtimer; /**<pointer to the timer calling test */
    mySerial *mserialPort; /**<pointer to the active serial port */
    std::vector<QStringList> macceptedForAutodetect = { /**<Vector of types of serial port device allowed for autodetect */
     /*Descriptions*/   {"CP210x"},
     /*Manufacturer*/   {"Silicon Labs"}
    };
    QString prevPortName; /**< name of the previously autoconnected serial port */
};

#endif // RRCMODULEAUTODETECT_H
