#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QWidget>

#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "serialsettingsdialog.h"
#include "myserial.h"
#include "rrccommunication.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace Ui {


class SerialMonitor;
}
/**
 * @brief The SerialMonitor class implementation of the serial monitor UI
 *
 * Class implements methods required for operationg of the serial monitor UI
 *
 * @author Aleksander Felisiak
 * @date $Date: 2019/08/17 12:22:00 $
 *
 * Contact: olek.felisiak@gmail.com
 *
 * Created on: Monday Aug 12th 2019
 */
class SerialMonitor : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief currentSetting returns current serial port settings
     * @return currentSettings for SerialSettingsDialog->mySerial object
     */
    mySerial *currentSetting();
    /**
     * @brief SerialMonitor class constructor
     * @param parent pointer to the object that called new part of the interface
     */
    explicit SerialMonitor(QWidget *parent = nullptr);
    /**
     * @brief externalSerialIndexChanger method called when index of the serial port in a combo box will be changed
     * in another window of UI to keep displayed data synchronized
     * @param index index of the currently set serial port in a combo box
     */
    void externalSerialIndexChanger(int index);

    ~SerialMonitor();

private slots:
    /**
     * @brief listAvaliablePorts method fills QComboBox::comboBoxPorts with a list
     * of the avaliable serial ports
     */
    void listAvaliablePorts();

    void on_pushButtonSearch_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

    /**
     * @brief readFromSerialPort slot responsible for reading message form serial port
     * @param message
     */
    void readFromSerialPort(QString message);

    void on_pushButtonSendCommand_clicked();

    void on_lineEditCommandLine_returnPressed();

    void on_pushButtonClearLog_clicked();

    void on_comboBoxPorts_currentIndexChanged(int index);

    void on_pushButtonSettings_clicked();
    /**
     * @brief AddToLogs method responsible for displaying informations in a log
     * connected with timestamp
     * @param message QString to display
     * @param direction of transmission
     */
    void AddToLogs(QString message, QString direction = ">>");

    /**
     * @brief serialPortConnectedInterfaceLockout method enalbes/disables part of the interface depending on
     * the fact is serial ort connected or not
     * @param status value to set
     */
    void serialPortConnectedInterfaceLockout(bool status);

private:

    /**
     * @brief sendCommandLineToSerialPort method responsible for sending content of
     * line input to over serial port
     */
    void sendCommandLineToSerialPort();
    Ui::SerialMonitor *ui = nullptr; /**< pointer to the graphic interface of the class */
    SerialSettingsDialog *serialSettings = nullptr; /**< pointer to the window with serial port settings*/
};

#endif // SERIALMONITOR_H
