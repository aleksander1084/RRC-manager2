#include "serialsettingsdialog.h"
#include "ui_serialsettingsdialog.h"

#include <QIntValidator>
#include <QLineEdit>
#include <QSerialPortInfo>

static const char blankString[] = QT_TRANSLATE_NOOP("SerialSettingsDialog", "N/A");

SerialSettingsDialog::SerialSettingsDialog(QWidget *parent) :
    QDialog(parent),
    currentSettings(new mySerial),
   ui(new Ui::SerialSettingsDialog),
   intValidator(new QIntValidator(0, 4000000, this))
{
    ui->setupUi(this);

    ui->baudRateBox_2->setInsertPolicy(QComboBox::NoInsert);

    connect(ui->applyButton_2, &QPushButton::clicked, this, &SerialSettingsDialog::apply);
    connect(ui->serialPortInfoListBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SerialSettingsDialog::showPortInfo);

    fillPortsParameters();
    fillPortsInfo();

    updateSettings();
}


SerialSettingsDialog::~SerialSettingsDialog()
{
    delete ui;
    ui = nullptr;
}

//mySerial SerialSettingsDialog::settings() const
//{
//    return currentSettings;
//}

void SerialSettingsDialog::externalSerialIndexChange(int idx)
{
    fillPortsInfo();
    //updateSettings();
    ui->serialPortInfoListBox_2->setCurrentIndex(idx);
}

void SerialSettingsDialog::showPortInfo(int idx)
{
    if(idx == -1)
        return;

    const QStringList list = ui->serialPortInfoListBox_2->itemData(idx).toStringList();
    ui->descriptionLabel_2->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
    ui->manufacturerLabel_2->setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
    ui->serialNumberLabel_2->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
    ui->locationLabel_2->setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));
    ui->vidLabel_2->setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : tr(blankString)));
    ui->pidLabel_2->setText(tr("Product Identifier: %1").arg(list.count() > 6 ? list.at(6) : tr(blankString)));
}

void SerialSettingsDialog::apply()
{
    updateSettings();
    emit serialIndexChanged(ui->serialPortInfoListBox_2->currentIndex());
    emit currentSettings->settingsChangedSignal();
    qDebug() << "Serial setting name: " << currentSettings->name;
    hide();
}

void SerialSettingsDialog::fillPortsParameters()
{
    ui->baudRateBox_2->addItem(QStringLiteral("1200"), QSerialPort::Baud1200);
    ui->baudRateBox_2->addItem(QStringLiteral("2400"), QSerialPort::Baud2400);
    ui->baudRateBox_2->addItem(QStringLiteral("4800"), QSerialPort::Baud4800);
    ui->baudRateBox_2->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateBox_2->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateBox_2->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateBox_2->addItem(QStringLiteral("57600"), QSerialPort::Baud57600);
    ui->baudRateBox_2->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudRateBox_2->setCurrentIndex(6);

    ui->dataBitsBox_2->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsBox_2->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox_2->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox_2->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsBox_2->setCurrentIndex(3);

    ui->parityBox_2->addItem(tr("None"), QSerialPort::NoParity);
    ui->parityBox_2->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityBox_2->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityBox_2->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityBox_2->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopBitsBox_2->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->stopBitsBox_2->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->stopBitsBox_2->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->flowControlBox_2->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->flowControlBox_2->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->flowControlBox_2->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void SerialSettingsDialog::fillPortsInfo()
{
    ui->serialPortInfoListBox_2->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        ui->serialPortInfoListBox_2->addItem(list.first(), list);
    }
}

void SerialSettingsDialog::updateSettings()
{
    qDebug() << "update settings";
    currentSettings->setName(ui->serialPortInfoListBox_2->currentText());

        currentSettings->baudRate = static_cast<QSerialPort::BaudRate>(
                    ui->baudRateBox_2->itemData(ui->baudRateBox_2->currentIndex()).toInt());

        currentSettings->dataBits = static_cast<QSerialPort::DataBits>(
                    ui->dataBitsBox_2->itemData(ui->dataBitsBox_2->currentIndex()).toInt());

        currentSettings->parity = static_cast<QSerialPort::Parity>(
                    ui->parityBox_2->itemData(ui->parityBox_2->currentIndex()).toInt());

        currentSettings->stopBits = static_cast<QSerialPort::StopBits>(
                    ui->stopBitsBox_2->itemData(ui->stopBitsBox_2->currentIndex()).toInt());

        currentSettings->flowControl = static_cast<QSerialPort::FlowControl>(
                    ui->flowControlBox_2->itemData(ui->flowControlBox_2->currentIndex()).toInt());
}
