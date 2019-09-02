#include "mainwindow.h"
#include "serialmonitor.h"
#include <QApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "parameter.h"
#include "moduleflasherwindow.h"
#include <QDebug>
#include <QMetaType>

#include "rrcmoduleflasher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
uint16_t x = 1024;

qDebug() << QString::number(double(x));
x = 256;
qDebug() << QString::number(double(x));
//Parameter<bool, 1> x;
//Parameter<int, 1> y;
//Parameter<uint8_t, 1> z;

//qDebug() << "bool type (true bool):" << x.isBool();
//qDebug() << "bool type (false int):" << y.isBool();
//qDebug() << "bool type (false uint8):" << z.isBool();

//qDebug() << "uint8_t type (false bool):" << x.isUint8_t();
//qDebug() << "uint8_t type (false int):" << y.isUint8_t();
//qDebug() << "uint8_t type (true uint8):" << z.isUint8_t();



    return a.exec();
}
