#include "moduleflasherwindow.h"
#include "ui_moduleflasherwindow.h"
#include "QDebug"
#include <math.h>


ModuleFlasherWindow::ModuleFlasherWindow(mySerial *n_serial, RRCCommunication *n_communication, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModuleFlasherWindow),
    serial(n_serial)
{
    mcommunication = n_communication;
    mflasher = new RRCModuleFlasher;
    advancedSettings = new ModuleFlasherWindowSettings(mflasher, this);
    if(mcommunication->isDeclared){
        delete mcommunication;
        mcommunication = nullptr;
    }
    mcommunication = new RRCCommunication(serial, mflasher);
    ui->setupUi(this);
    SetInputModesDisabled();
    SetInputModesEnabled();
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, this, &ModuleFlasherWindow::checkAllInputs);
    QObject::connect(ui->radioButton_automatic, &QPushButton::toggled, advancedSettings, &ModuleFlasherWindowSettings::setInputMode);
    groupRadioButtons();

    fillSerialPorts();
    qDebug()<<"starting widnow";
    QObject::connect(serial, &mySerial::nameChangedSignal, this, &ModuleFlasherWindow::fillSerialPorts);
    serialPortConnectedInterfaceLockout(serial->isOpen());
    QObject::connect(serial, &mySerial::serialConnectionStuatusSignal, this, &ModuleFlasherWindow::serialPortConnectedInterfaceLockout);
    QObject::connect(serial, &mySerial::searchSignal, this, &ModuleFlasherWindow::fillSerialPorts);
    dispalyModuleValues();
    QObject::connect(mflasher, &RRCModule::parameterChanged, this, &ModuleFlasherWindow::dispalyModuleValues);

    mcommunication->readDevice();
}

ModuleFlasherWindow::~ModuleFlasherWindow()
{
    QObject::disconnect(mflasher, &RRCModule::parameterChanged, this, &ModuleFlasherWindow::dispalyModuleValues);
    delete ui;
    ui = nullptr;
    delete mflasher;
    mflasher = nullptr;
    delete advancedSettings;
    advancedSettings = nullptr;
    for (int i = 0; i < 6; ++i) {
        delete inputs[i];
        inputs[i] = nullptr;
    }
    //qDebug() << "flasher window killed";
}

void ModuleFlasherWindow::SetInputModesDisabled(){
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i1n, &QRadioButton::click);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i2n, &QRadioButton::click);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i3n, &QRadioButton::click);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i4n, &QRadioButton::click);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i5n, &QRadioButton::click);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i6n, &QRadioButton::click);

    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i1a, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i2a, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i3a, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i4a, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i5a, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i6a, &QRadioButton::setDisabled);

    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i1d, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i2d, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i3d, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i4d, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i5d, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i6d, &QRadioButton::setDisabled);

    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i1m, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i2m, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i3m, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i4m, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i5m, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i6m, &QRadioButton::setDisabled);

    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i1n, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i2n, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i3n, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i4n, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i5n, &QRadioButton::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i6n, &QRadioButton::setDisabled);

    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_activation, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_deactivation, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_maintain, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_InputMode, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_unactive, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_i1, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_i2, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_i3, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_i4, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_i5, &QLabel::setDisabled);
    QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->label_i6, &QLabel::setDisabled);
}



void ModuleFlasherWindow::SetInputModesEnabled(){


    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i1a, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i2a, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i3a, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i4a, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i5a, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i6a, &QRadioButton::setEnabled);

    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i1d, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i2d, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i3d, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i4d, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i5d, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i6d, &QRadioButton::setEnabled);

    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i1m, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i2m, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i3m, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i4m, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i5m, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i6m, &QRadioButton::setEnabled);

    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i1n, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i2n, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i3n, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i4n, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i5n, &QRadioButton::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i6n, &QRadioButton::setEnabled);

    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_activation, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_deactivation, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_maintain, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_InputMode, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_unactive, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_i1, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_i2, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_i3, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_i4, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_i5, &QLabel::setEnabled);
    QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->label_i6, &QLabel::setEnabled);

}

void ModuleFlasherWindow::dispalyModuleValues()
{
//    QString sn = "SN: ";
//            sn += mflasher->serialNumber();
//            qDebug() << sn;
//    ui->label_SN->setText(sn);
//    ui->label_SN->repaint();

    setLabel("SN: ", mflasher->serialNumber(), ui->label_SN);
    setLabel("SV: ", mflasher->softwareVersion(), ui->label_SFN);
    setLabel("Last update: ", mflasher->lastUpdate(), ui->label_lastUpdate);

    if(mflasher->authenticity() != "Module is authentic.")
    {
        ui->label_authenticity->setStyleSheet("QLabel { color : red; }");
    }
    else
    {
        ui->label_authenticity->setStyleSheet("QLabel { color : black; }");
    }
    setLabel("", mflasher->authenticity(), ui->label_authenticity);

    ui->label_settingMatch->hide(); //TODO: check with database

    setMode();

    setLineEditAndSlider(ui->lineEdit_flashPeriod, mflasher->flashingPeriod());
    setLineEditAndSlider(ui->lineEdit_timeDeactivation, mflasher->timeout());
    setLineEditAndSlider(ui->lineEdit_maxTime, mflasher->masterTimeout());
}

//void ModuleFlasherWindow::reject()
//{
//    ModuleFlasherWindow::~ModuleFlasherWindow();
//}

void ModuleFlasherWindow::setLabel(QString tag, QString text, QLabel *label)
{
    label->setText(tag + text);
    label->repaint();
}

void ModuleFlasherWindow::readInputMode(int inputNumber)
{
    inputs[inputNumber]->button(mflasher->inputMode(inputNumber))->setChecked(true);
}

void ModuleFlasherWindow::groupRadioButtons()
{
    inputs[0] = ui->buttonGroup_i1;
    inputs[1] = ui->buttonGroup_i2;
    inputs[2] = ui->buttonGroup_i3;
    inputs[3] = ui->buttonGroup_i4;
    inputs[4] = ui->buttonGroup_i5;
    inputs[5] = ui->buttonGroup_i6;

    inputs[0]->setId(ui->radioButton_i1n, 0);
    inputs[0]->setId(ui->radioButton_i1a, 1);
    inputs[0]->setId(ui->radioButton_i1d, 2);
    inputs[0]->setId(ui->radioButton_i1m, 3);

    inputs[1]->setId(ui->radioButton_i2n, 0);
    inputs[1]->setId(ui->radioButton_i2a, 1);
    inputs[1]->setId(ui->radioButton_i2d, 2);
    inputs[1]->setId(ui->radioButton_i2m, 3);

    inputs[2]->setId(ui->radioButton_i3n, 0);
    inputs[2]->setId(ui->radioButton_i3a, 1);
    inputs[2]->setId(ui->radioButton_i3d, 2);
    inputs[2]->setId(ui->radioButton_i3m, 3);

    inputs[3]->setId(ui->radioButton_i4n, 0);
    inputs[3]->setId(ui->radioButton_i4a, 1);
    inputs[3]->setId(ui->radioButton_i4d, 2);
    inputs[3]->setId(ui->radioButton_i4m, 3);

    inputs[4]->setId(ui->radioButton_i5n, 0);
    inputs[4]->setId(ui->radioButton_i5a, 1);
    inputs[4]->setId(ui->radioButton_i5d, 2);
    inputs[4]->setId(ui->radioButton_i5m, 3);

    inputs[5]->setId(ui->radioButton_i6n, 0);
    inputs[5]->setId(ui->radioButton_i6a, 1);
    inputs[5]->setId(ui->radioButton_i6d, 2);
    inputs[5]->setId(ui->radioButton_i6m, 3);
}

bool ModuleFlasherWindow::setMode()
{
    if(mflasher->mode())
    {
        ui->radioButton_automatic->setChecked(true);
        emit ui->radioButton_automatic->clicked(true);
    }
    else
    {
        ui->radioButton_manual->setChecked(true);
        emit ui->radioButton_manual->clicked(true);
    }

    return mflasher->mode();
}

void ModuleFlasherWindow::setLineEditAndSlider(QLineEdit *lineEdit, double n_value)
{
    lineEdit->setText(QString::number(n_value));
    emit lineEdit->textEdited(lineEdit->text());
}

void ModuleFlasherWindow::setLineEditAndSlider(QLineEdit *lineEdit, float n_value)
{
    setLineEditAndSlider(lineEdit, double(n_value));
}

void ModuleFlasherWindow::setLineEditAndSlider(QLineEdit *lineEdit, int n_value)
{
    setLineEditAndSlider(lineEdit, double(n_value));
}

void ModuleFlasherWindow::setLineEditAndSlider(QLineEdit *lineEdit, uint8_t n_value)
{
    setLineEditAndSlider(lineEdit, double(n_value));
}

void ModuleFlasherWindow::setLineEditAndSlider(QLineEdit *lineEdit, uint16_t n_value)
{
    setLineEditAndSlider(lineEdit, double(n_value));
}

void ModuleFlasherWindow::updateModuleSettings()
{
    //last update
    QString currentDate = QDateTime::currentDateTime().toString("yyyy.MM.dd");
    QStringList sections = currentDate.split(".");
    mflasher->lastUpdate(sections.value(2).toInt(), sections.value(1).toInt(), sections.value(0).toInt());

    //mode
    mflasher->mode(ui->radioButton_automatic->isChecked());

    //buttonModes
    for(int i = 0; i < 6 ; ++i)
    {
        qDebug() << "MODE: " << mflasher->mode();
        if(mflasher->mode())
        {
            mflasher->inputMode(i, inputs[i]->checkedId());
        }
        else
        {
            mflasher->inputMode(i, 0);
        }
        qDebug() << "flasher input mode: " << QString::number(mflasher->inputMode(i));

    }

    //flashing period
    mflasher->flashingPeriod(ui->lineEdit_flashPeriod->text().toFloat());

    //master timeout
    mflasher->masterTimeout(uint16_t(ui->lineEdit_maxTime->text().toInt()));

    //timeout
    mflasher->timeout(uint16_t(ui->lineEdit_timeDeactivation->text().toInt()));

    //advanced settings
    advancedSettings->updateAdvancedSettings();

    mcommunication->updateDevice();
}

void ModuleFlasherWindow::serialPortConnectedInterfaceLockout(bool status)
{
    ui->pushButtonSearch->setEnabled(!status);
    ui->pushButtonConnect->setEnabled(!status);
    ui->comboBoxSerialPorts->setEnabled(!status);
    ui->pushButtonDisconnect->setEnabled(status);
}

void ModuleFlasherWindow::checkAllInputs()
{
    for(int i = 0; i < 6; ++i)
    {
        readInputMode(i);
    }
}

void ModuleFlasherWindow::fillSerialPorts()
{
    qDebug() << "Flasher serial port name:" << serial->name;
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    ui->comboBoxSerialPorts->clear();
    for(int i = 0; i < devices.count(); i++)
    {
        ui->comboBoxSerialPorts->addItem(devices.at(i).portName() + " " + devices.at(i).description());
        if(serial->name == devices.at(i).portName())
        {
            ui->comboBoxSerialPorts->setCurrentIndex(i);
        }
    }
}


void ModuleFlasherWindow::on_horizontalSlider_flashingPeriod_sliderMoved(int position)
{
    ui->lineEdit_flashPeriod->setText(QString::number(0.1*position));
}



void ModuleFlasherWindow::on_lineEdit_flashPeriod_textEdited(const QString &arg1)
{
    ui->horizontalSlider_flashingPeriod->setValue(int(10*arg1.toFloat()));
}

void ModuleFlasherWindow::on_horizontalSlider_timeDeactivation_sliderMoved(int position)
{
    ui->lineEdit_timeDeactivation->setText(QString::number(position));
}

void ModuleFlasherWindow::on_lineEdit_timeDeactivation_textEdited(const QString &arg1)
{
    ui->horizontalSlider_timeDeactivation->setValue(arg1.toInt());
}

void ModuleFlasherWindow::on_horizontalSlider_maxTime_sliderMoved(int position)
{
     ui->lineEdit_maxTime->setText(QString::number(position));
}

void ModuleFlasherWindow::on_lineEdit_maxTime_textEdited(const QString &arg1)
{
    ui->horizontalSlider_maxTime->setValue(arg1.toInt());
}

void ModuleFlasherWindow::on_pushButton_AdvencedSettings_clicked()
{
//    ModuleFlasherASWindow advancedSettings;
//    advancedSettings.setModal(true);
//    advancedSettings.exec();
    advancedSettings->show();
}

void ModuleFlasherWindow::on_pushButtonSearch_clicked()
{
    emit serial->searchSignal();
}

void ModuleFlasherWindow::on_pushButtonConnect_clicked()
{
    if(ui->comboBoxSerialPorts->count() == 0)
    {
        return;
    }
    emit serial->serialIndexChanged(ui->comboBoxSerialPorts->currentIndex());
    serial->connectSerialPort();
}

void ModuleFlasherWindow::on_pushButtonDisconnect_clicked()
{
    serial->disconnectSerialPort();
}

void ModuleFlasherWindow::on_pushButton_updateModule_clicked()
{
    updateModuleSettings();
//    qDebug() << "MODE:" << mflasher->mode();
//    qDebug() << "Flashing period" <<QString::number(double(mflasher->flashingPeriod()), 'f', 1);
//    qDebug() << "timeout" << mflasher->timeout();
//    qDebug() << "master timeout" << mflasher->masterTimeout();
//    for(int i = 0; i <6; i++)
//    {
//        qDebug() << "input" << QString::number(i+1) << " mode: " << QString::number(mflasher->inputMode(i));
//    }
//    qDebug() << "LAST UPDATE: " << mflasher->lastUpdate();
//    for (int i = 0; i<6; ++i) {
//        qDebug() << "input" <<QString::number(i+1) << " activation state is " << mflasher->activeInputState(i);
//        qDebug() << "input" <<QString::number(i+1) << " activation delay: "<<mflasher->inputActivationDelay(i);
//        qDebug() << "input" <<QString::number(i+1) << " deactivation delay: "<<mflasher->inputDeactivationDelay(i);
//    }
    dispalyModuleValues();
}

void ModuleFlasherWindow::on_pushButton_loadModule_clicked()
{
    mcommunication->readDevice();
}
