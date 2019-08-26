#include "myserial.h"

mySerial::mySerial() :  baudRate(static_cast<QSerialPort::BaudRate>(QSerialPort::Baud57600)),
                        dataBits(static_cast<QSerialPort::DataBits>(QSerialPort::Data8)),
                        parity(static_cast<QSerialPort::Parity>(QSerialPort::NoParity)),
                        stopBits(static_cast<QSerialPort::StopBits>(QSerialPort::OneStop)),
                        flowControl(static_cast<QSerialPort::FlowControl>(QSerialPort::NoFlowControl))
{
    serialPort = new QSerialPort;
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    if(serialPorts.count() != 0)
    {
        name = serialPorts.at(0).portName();
    }
}

mySerial::mySerial(QString n_name, qint32 n_baudRate, QSerialPort::DataBits n_dataBits,
                   QSerialPort::Parity n_parity, QSerialPort::StopBits n_stopBits,
                   QSerialPort::FlowControl n_flowControl)
                    : name(n_name),
                      baudRate(n_baudRate),
                      dataBits(n_dataBits),
                      parity(n_parity),
                      stopBits(n_stopBits),
                      flowControl(n_flowControl)
{
    serialPort = new QSerialPort;
}

mySerial::mySerial(qint32 n_baudRate, QSerialPort::DataBits n_dataBits,
                   QSerialPort::Parity n_parity, QSerialPort::StopBits n_stopBits,
                   QSerialPort::FlowControl n_flowControl)
                    : baudRate(n_baudRate),
                      dataBits(n_dataBits),
                      parity(n_parity),
                      stopBits(n_stopBits),
                      flowControl(n_flowControl)
{
    serialPort = new QSerialPort;
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    if(serialPorts.count() != 0)
    {
        name = serialPorts.at(0).portName();
    }
}

mySerial::mySerial(qint32 n_baudRate)
                    :baudRate(n_baudRate),
                     dataBits(static_cast<QSerialPort::DataBits>(QSerialPort::Data8)),
                     parity(static_cast<QSerialPort::Parity>(QSerialPort::NoParity)),
                     stopBits(static_cast<QSerialPort::StopBits>(QSerialPort::OneStop)),
                     flowControl(static_cast<QSerialPort::FlowControl>(QSerialPort::NoFlowControl))
{
    serialPort = new QSerialPort;
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    if(serialPorts.count() != 0)
    {
        name = serialPorts.at(0).portName();
    }
}

mySerial::~mySerial()
{
    delete serialPort;
}

QString mySerial::connectSerialPort()
{
    serialPort->setPortName(name);
    qDebug() << "Connecting to " + serialPort->portName();
    if(!serialPort->isOpen())
    {
        if(serialPort->open(QSerialPort::ReadWrite))
        {
          this->serialPort->setBaudRate(baudRate);
            //qDebug() << baudRate;
          this->serialPort->setDataBits(dataBits);
           // qDebug() << dataBits;
          this->serialPort->setParity(parity);
            //qDebug() << parity;
          this->serialPort->setStopBits(stopBits);
            //qDebug() << stopBits;
          this->serialPort->setFlowControl(flowControl);
            //qDebug() << flowControl;

           QObject::connect(serialPort, &QSerialPort::readyRead, this, &mySerial::readFromSerialPort);


        } else {
          return "Failed to open. Port is already open.";
        }
    }
    return "Connected to the serial port: " + serialPort->portName();
}

QString mySerial::disconnectSerialPort()
{
    if(serialPort->isOpen())
    {
        serialPort->close();
    }
    if(!serialPort->isOpen())
    {
        return "Serial port " + serialPort->portName() + " is closed.";
    }
    else
    {
        return "Failed to close serial port " + serialPort->portName();
    }
}

bool mySerial::isOpen()
{
    return serialPort->isOpen();
}

void mySerial::readFromSerialPort()
{
    QString line;
    //qDebug() << "ENTERED";

        const QByteArray data = this->serialPort->readAll();

        line = QString::fromStdString(data.toStdString());
        emit newMessageReceived(line);
}

void mySerial::sendMessageToSerialPort(QString message)
{
    if(serialPort->isOpen() && serialPort->isWritable())
    {
        serialPort->write(message.toStdString().c_str());
        emit newMessageSent(message);
    }
}