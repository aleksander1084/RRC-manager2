#include "mainwindow.h"
#include "serialmonitor.h"
#include <QApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "parameter.h"
#include "moduleflasherwindow.h"
#include <QDebug>

#include "rrcmoduleflasher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    int ufo[5]= {1,2,3,4,5};
//    Parameter<int, 5> x("Serial", "SN", ufo, sizeof (ufo)/sizeof (ufo[0]));
//    qDebug() << x.name << " " << x.values[0];
//    qDebug() << x.name << " " << x.values[1];
    ModuleFlasherWindow x;
    x.show();

    RRCModuleFlasher y;
    qDebug() << "readed parameter " << y.readParameter<float>("FPD");
    float n_val[] = {float(1.4)};
    y.setParameterValue("FPD", n_val, 1);
    qDebug() << "readed parameter " << y.readParameter<float>("FPD");


    return a.exec();
}
