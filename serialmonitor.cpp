#include "serialmonitor.h"
#include "ui_serialmonitor.h"

#include <QMessageBox>

mySerial *SerialMonitor::currentSetting()
{
    return serialSettings->currentSettings;
}

SerialMonitor::SerialMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialMonitor),
    serialSettings(new SerialSettingsDialog)
{
    ui->setupUi(this);
    qDebug() << "Searching for Serial Ports";
    listAvaliablePorts();

    QObject::connect(ui->pushButtonSettings, &QPushButton::clicked, serialSettings, &SerialSettingsDialog::show);
    QObject::connect(serialSettings, &SerialSettingsDialog::serialIndexChanged, ui->comboBoxPorts, &QComboBox::setCurrentIndex);
    serialPortConnectedInterfaceLockout(false);
    QObject::connect(serialSettings->currentSettings, &mySerial::serialConnectionStuatusSignal, this, &SerialMonitor::serialPortConnectedInterfaceLockout);
    QObject::connect(this->serialSettings->currentSettings, &mySerial::newMessageReceived,
                     this, &SerialMonitor::readFromSerialPort);
    QObject::connect(this->serialSettings->currentSettings, &mySerial::newMessageSent,
                     this, &SerialMonitor::AddToLogs);
    QObject::connect(serialSettings->currentSettings, &mySerial::searchSignal, this, &SerialMonitor::listAvaliablePorts);
}

SerialMonitor::~SerialMonitor()
{
    delete ui;
    ui = nullptr;
    delete serialSettings;
    serialSettings = nullptr;
}

void SerialMonitor::on_pushButtonSearch_clicked()
{
    qDebug() << "Searching for Serial Ports";
    this->AddToLogs("Searching for Serial Ports", "<>");
    //listAvaliablePorts();
    emit serialSettings->currentSettings->searchSignal();
}

void SerialMonitor::listAvaliablePorts()
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

void SerialMonitor::sendCommandLineToSerialPort()
{
     QString message = ui->lineEditCommandLine->text();
     ui->lineEditCommandLine->clear();
     this->serialSettings->currentSettings->sendMessageToSerialPort(message);
}

void SerialMonitor::on_pushButtonConnect_clicked()
{

    if(ui->comboBoxPorts->count() == 0) {
      this->AddToLogs("No device found.","<>");
      return;
    }
    QString message = serialSettings->currentSettings->connectSerialPort();
    qDebug() << message;
//    if(serialSettings->currentSettings->isOpen())
//    {
//        serialPortConnectedInterfaceLockout(true);
//    }
   // AddToLogs(message, "<>");
}

void SerialMonitor::on_pushButtonDisconnect_clicked()
{
    QString message = serialSettings->currentSettings->disconnectSerialPort();
    qDebug() << message;
//    if(!serialSettings->currentSettings->isOpen())
//    {
//      serialPortConnectedInterfaceLockout(false);
//    }
    //AddToLogs(message, "<>");
}

void SerialMonitor::readFromSerialPort(QString message)
{
    //qDebug()<< message;
    this->AddToLogs(message, ">>");
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

    QString portName = ui->comboBoxPorts->currentText().split(" ").first();
    qDebug() << "serial monitor";
    serialSettings->currentSettings->setName(portName);
    //qDebug() << "serial monitor name: " << serialSettings->currentSettings->name;
    serialSettings->externalSerialIndexChange(index);

    emit serialSettings->currentSettings->settingsChangedSignal();
}

void SerialMonitor::on_pushButtonSettings_clicked()
{
    serialSettings->externalSerialIndexChange(ui->comboBoxPorts->currentIndex());
}
