#include "serialmonitor.h"
#include "ui_serialmonitor.h"

SerialMonitor::SerialMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialMonitor)
{
    ui->setupUi(this);
    qDebug() << "Searching for Serial Ports";
    ListAvaliablePorts();
    this->serialPort = new QSerialPort(this);
}

SerialMonitor::~SerialMonitor()
{
    delete ui;
}

void SerialMonitor::on_pushButtonSearch_clicked()
{
    qDebug() << "Searching for Serial Ports";
    this->AddToLogs("Searching for Serial Ports", "<>");
    ListAvaliablePorts();
}

void SerialMonitor::ListAvaliablePorts()
{
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    ui->comboBoxPorts->clear();
    for(int i = 0; i < devices.count(); i++)
    {
        qDebug() <<devices.at(i).portName() << devices.at(i).description();
        this->AddToLogs("Found device: " + devices.at(i).portName() + " " + devices.at(i).description(), "<>");
        ui->comboBoxPorts->addItem(devices.at(i).portName() + " " + devices.at(i).description());
    }
}

void SerialMonitor::AddToLogs(QString message, QString direction)
{
    if(this->isVisible())
    {
        QString currentDataTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
        ui->textEditSerialLog->append(currentDataTime + " " + direction + " " + message);
    }

}

void SerialMonitor::sendMessageToSerialPort(QString message)
{
    if(this->serialPort->isOpen() && this->serialPort->isWritable())
    {
        this->AddToLogs(message, ">>");
        this->serialPort->write(message.toStdString().c_str());
    }
    else {
        this->AddToLogs("Can't send a message.\n Port is closed or can't recive data.","<>");
    }
}

void SerialMonitor::sendCommandLineToSerialPort()
{
     QString message = ui->lineEditCommandLine->text();
     ui->lineEditCommandLine->clear();
     this->sendMessageToSerialPort(message);
}

void SerialMonitor::on_pushButtonConnect_clicked()
{
    if(ui->comboBoxPorts->count() == 0) {
      this->AddToLogs("No device found.","<>");
      return;
    }

    QString portName = ui->comboBoxPorts->currentText().split(" ").first();
    this->serialPort->setPortName(portName);
    qDebug() << "connecting to the port";
    qDebug() << portName;

    // Open and set serial port:
    if(!serialPort->isOpen()){
        if(serialPort->open(QSerialPort::ReadWrite)) {
          this->serialPort->setBaudRate(QSerialPort::Baud57600);
          this->serialPort->setDataBits(QSerialPort::Data8);
          this->serialPort->setParity(QSerialPort::NoParity);
          this->serialPort->setStopBits(QSerialPort::OneStop);
          this->serialPort->setFlowControl(QSerialPort::NoFlowControl);

          this->AddToLogs("Serial port is open", "<>");
           connect(this->serialPort, SIGNAL(readyRead()), this, SLOT(readFromSerialPort()));
        } else {
          this->AddToLogs("Failed to open serial port","<>");
        }
    }
    else {
        this->AddToLogs("Serial port already open.", "<>");
        qDebug() << "Serial port already open";
    }

}

void SerialMonitor::on_pushButtonDisconnect_clicked()
{
    if(this->serialPort->isOpen()){
        this->serialPort->close();
        this->AddToLogs("Serial port closed", "<>");
        qDebug() << "Serial port closed";
    }
    else{
        this->AddToLogs("Serial port not open, can not be closed.", "<>");
        qDebug() << "Serial port not open, can not be closed.";
    }
}

void SerialMonitor::readFromSerialPort()
{
    const QByteArray data = this->serialPort->readAll();

    QString line = QString::fromStdString(data.toStdString());
    this->AddToLogs(line, "<<");

//    while(this->serialPort->canReadLine()) {
//        QString line = this->serialPort->readAll();
//        qDebug() << line;

//        QString terminator = "\r";
//        int pos = line.lastIndexOf(terminator);
//        //qDebug() << line.left(pos);

//        this->AddToLogs(line.left(pos),"<<");
//      }
}

void SerialMonitor::on_pushButtonSendCommand_clicked()
{
    this->sendCommandLineToSerialPort();

}

void SerialMonitor::on_lineEditCommandLine_returnPressed()
{
    this->sendCommandLineToSerialPort();
}

void SerialMonitor::on_pushButtonClearLog_clicked()
{
    ui->textEditSerialLog->clear();
}
