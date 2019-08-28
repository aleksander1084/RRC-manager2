#include "moduleflasherwindow.h"
#include "ui_moduleflasherwindow.h"
//#include "ui_modulelidaraswindow.h"
//#include "moduleflasheraswindow.h"
#include "QDebug"

ModuleFlasherWindow::ModuleFlasherWindow(mySerial *n_serial, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModuleFlasherWindow),
    serial(n_serial)
{
    ui->setupUi(this);
    SetInputModesDisabled();
    SetInputModesEnabled();
   // QObject::connect(ui->radioButton_manual, &QRadioButton::clicked, ui->radioButton_i1a, &QRadioButton::setDisabled);
    //QObject::connect(ui->radioButton_automatic, &QRadioButton::clicked, ui->radioButton_i1a, &QRadioButton::setEnabled);

    fillSerialPorts();

    connect(serial, &mySerial::nameChangedSignal, this, &ModuleFlasherWindow::fillSerialPorts);

}

ModuleFlasherWindow::~ModuleFlasherWindow()
{
    delete ui;
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
}
