#include "serialmonitor.h"
#include "ui_serialmonitor.h"

#include <QMessageBox>

SerialMonitor::SerialMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialMonitor),
    serialSettings(new SerialSettingsDialog)
{
    ui->setupUi(this);
    qDebug() << "Searching for Serial Ports";
    listAvaliablePorts();
    //this->serialPort = new QSerialPort(this);

    connect(ui->pushButtonSettings, &QPushButton::clicked, serialSettings, &SerialSettingsDialog::show);
    connect(serialSettings, &SerialSettingsDialog::serialIndexChanged, ui->comboBoxPorts, &QComboBox::setCurrentIndex);
    serialPortConnectedInterfaceLockout(false);

}

SerialMonitor::~SerialMonitor()
{
    delete ui;
    delete serialSettings;
}

void SerialMonitor::on_pushButtonSearch_clicked()
{
    qDebug() << "Searching for Serial Ports";
    this->AddToLogs("Searching for Serial Ports", "<>");
    listAvaliablePorts();
}

void SerialMonitor::listAvaliablePorts()//universal equivalent in mySerial class, TODO update
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

void SerialMonitor::serialPortConnectedInterfaceLockout(bool status)
{
    ui->pushButtonSearch->setEnabled(!status);
    ui->pushButtonConnect->setEnabled(!status);
    ui->pushButtonSettings->setEnabled(!status);
    ui->comboBoxPorts->setEnabled(!status);

    ui->lineEditCommandLine->setEnabled(status);
    ui->pushButtonSendCommand->setEnabled(status);
    ui->pushButtonDisconnect->setEnabled(status);
}

void SerialMonitor::AddToLogs(QString message, QString direction)
{
    if(this->isVisible())
    {
        QString currentDataTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
        ui->textEditSerialLog->append(currentDataTime + " " + direction + " " + message);
    }

}

//void SerialMonitor::sendMessageToSerialPort(QString message)
//{
//    if(this->serialPort->isOpen() && this->serialPort->isWritable())
//    {
//        this->AddToLogs(message, ">>");
//        this->serialPort->write(message.toStdString().c_str());
//    }
//    else {
//        this->AddToLogs("Can't send a message.\n Port is closed or can't recive data.","<>");
//    }
//}

void SerialMonitor::sendCommandLineToSerialPort()
{
     QString message = ui->lineEditCommandLine->text();
     ui->lineEditCommandLine->clear();
     this->serialSettings->currentSettings->sendMessageToSerialPort(message);
     //this->sendMessageToSerialPort(message);

}

void SerialMonitor::on_pushButtonConnect_clicked()
{

    if(ui->comboBoxPorts->count() == 0) {
      this->AddToLogs("No device found.","<>");
      return;
    }
//    mySerial port = serialSettings->settings();
//    this->serialPort->setPortName(port.name);
//    qDebug() << "connecting to the port";
//    qDebug() << port.name;

//    // Open and set serial port:
//    if(!serialPort->isOpen()){
//        if(serialPort->open(QSerialPort::ReadWrite)) {
//          this->serialPort->setBaudRate(port.baudRate);
//            qDebug() << port.baudRate;
//          this->serialPort->setDataBits(port.dataBits);
//          this->serialPort->setParity(port.parity);
//          this->serialPort->setStopBits(port.stopBits);
//          this->serialPort->setFlowControl(port.flowControl);

//          this->AddToLogs("Serial port is open", "<>");
//           connect(this->serialPort, SIGNAL(readyRead()), this, SLOT(readFromSerialPort()));

//           serialPortConnectedInterfaceLockout(true);
//        } else {
//          this->AddToLogs("Failed to open serial port","<>");
//        }
//    }
//    else {
//        this->AddToLogs("Serial port already open.", "<>");
//        qDebug() << "Serial port already open";
//    }
    QString message = serialSettings->currentSettings->connectSerialPort();
    qDebug() << message;
    if(serialSettings->currentSettings->isOpen())
    {
        serialPortConnectedInterfaceLockout(true);
    }
    AddToLogs(message, "<>");
    QObject::connect(this->serialSettings->currentSettings, &mySerial::newMessageReceived,
                     this, &SerialMonitor::readFromSerialPort);
    QObject::connect(this->serialSettings->currentSettings, &mySerial::newMessageSent,
                     this, &SerialMonitor::AddToLogs);


}

void SerialMonitor::on_pushButtonDisconnect_clicked()
{
//    if(this->serialPort->isOpen()){
//        this->serialPort->close();
//        this->AddToLogs("Serial port closed", "<>");
//        qDebug() << "Serial port closed";
//    }
//    else{
//        this->AddToLogs("Serial port not open, can not be closed.", "<>");
//        qDebug() << "Serial port not open, can not be closed.";
//    }
    QString message = serialSettings->currentSettings->disconnectSerialPort();
    qDebug() << message;
    if(!serialSettings->currentSettings->isOpen())
    {
      serialPortConnectedInterfaceLockout(false);
    }
    AddToLogs(message, "<>");


}

void SerialMonitor::readFromSerialPort(QString message)
{
//    const QByteArray data = this->serialPort->readAll();

//    QString line = QString::fromStdString(data.toStdString());
    qDebug()<< message;
    this->AddToLogs(message, "<<");
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

void SerialMonitor::on_comboBoxPorts_currentIndexChanged(int index)
{
    serialSettings->externalSerialIndexChange(index);
    QString portName = ui->comboBoxPorts->currentText().split(" ").first();
    serialSettings->currentSettings->name = portName;
    //qDebug() << serialSettings->currentSettings.name;
}

void SerialMonitor::on_pushButtonSettings_clicked()
{
    serialSettings->externalSerialIndexChange(ui->comboBoxPorts->currentIndex());
}
