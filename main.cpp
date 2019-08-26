#include "mainwindow.h"
#include "serialmonitor.h"
#include <QApplication>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "parameter.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    std::array<int, 5> ufo = {1,2,3,4,5};
//    int ufoSize = ufo.size();
    int ufo[5]= {1,2,3,4,5};
    Parameter<int, 5> x("Serial", "SN", ufo, sizeof (ufo)/sizeof (ufo[0]));
    qDebug() << x.name << " " << x.values[0];
    qDebug() << x.name << " " << x.values[1];

    return a.exec();
}
