#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QList>
#include <QDateTime>
#include <QObject>

/**
 * @brief implementations of the serial port
 *
 * Class implements methods and parameters required to operate serial port
 *
 * @author Aleksander Felisiak
 * @date $Date: 2019/08/17 12:22:00 $
 *
 * Contact: olek.felisiak@gmail.com
 *
 * Created on: Saturday Aug 17th 2019
 *
 */
class mySerial : public QObject
{

    Q_OBJECT

public:


    /**
     * @brief mySerial main constructor
     */
    mySerial();

    /**
     * @brief mySerial constructor with option for all serial port parameters
     * @param n_name serial port name
     * @param n_baudRate baud rate to set
     * @param n_dataBits number of data bits
     * @param n_parity type of parity
     * @param n_stopBits number of stop bits
     * @param n_flowControl type of flow control
     */
    mySerial(QString n_name, qint32 n_baudRate, QSerialPort::DataBits n_dataBits,
             QSerialPort::Parity n_parity, QSerialPort::StopBits n_stopBits,
             QSerialPort::FlowControl n_flowControl);

    /**
     * @brief mySerial constructor for not default serial port when serial port name is unknown
     * @param n_baudRate baud rate to set
     * @param n_dataBits number of data bits
     * @param n_parity type of parity
     * @param n_stopBits number of stop bits
     * @param n_flowControl type of flow control
     */
    mySerial(qint32 n_baudRate, QSerialPort::DataBits n_dataBits,
             QSerialPort::Parity n_parity, QSerialPort::StopBits n_stopBits,
             QSerialPort::FlowControl n_flowControl);

    /**
     * @brief mySerial constructor when all parameters except baud rate should stay default
     * @param n_baudRate baud rate to set
     */
    mySerial(qint32 n_baudRate);

    ~mySerial();

    /**
     * @brief connectSerialPort method responsible for connecting to the serial port
     * @return returns information about connecion success or fail
     */
    QString connectSerialPort();

    /**
     * @brief disconnectSerialPort method responsible for disconnecting serial port
     * @return returns information about disconnection sucess or fail
     */
    QString disconnectSerialPort();

    /**
     * @brief isOpen method responsible to return information is serial port connection open,
     * @return value of the QIODevice::isOpen() of provate member QSerialPort::serialPort
     */
    bool isOpen();

    /**
     * @brief sendMessageToSerialPort sends message over serial port to the device
     * @param message contains message that has to be send
     */
    void sendMessageToSerialPort(QString message);

    /**
     * @brief operator = assigment operator for mySerial that is inhariting after QObject that
     * doesn't include assigment in this case overload has to copy member values into another variable
     * @param other
     * @return values of assigned variable members parameters
     */
    mySerial &operator = (mySerial &&other);

    QString name; /**< contains name of the serial port, format "COMX" */
    qint32 baudRate; /**< contains value of the baudrate to communicate via serial port */
    QSerialPort::DataBits dataBits; /**< contains number of data bits in a serial port communication */
    QSerialPort::Parity parity; /**< contains type of the parity for the serial port */
    QSerialPort::StopBits stopBits; /**< contains number of stoop bits for the serial port communication */
    QSerialPort::FlowControl flowControl; /**< contains type of the flow control for the communication */
    //bool localEchoEnabled;



signals:

    /**
     * @brief settingsChangedSignal function called when Serial Port Settings are changed and there
     * is a need to send signal about this event
     * @param newSettings contains set of the actual settings for other parts of the app
     */
    void settingsChangedSignal();

    /**
     * @brief newMessageSent signal send when new message will be sent
     * required for the serial monitor to print a log
     * @param message
     */
    void newMessageSent(QString message, QString direction = "<<");

    /**
     * @brief newMessageReceived signal called when new message is send, needed for serial monitor log
     * @param message message that was send
     * @param direction direction needed to display message on a serial monitor, allways has it's default value
     */
    void newMessageReceived(QString message, QString direction = ">>");

private slots:
    /**
     * @brief readFromSerialPort reads message from the serial port when it's avaliable
     * @return QString with a received message
     */
    void readFromSerialPort();

private:
    QSerialPort *serialPort = nullptr; /**< Private member containing serial port*/


};

#endif // MYSERIAL_H
