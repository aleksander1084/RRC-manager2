#include "mainwindow.h"
#include "serialmonitor.h"
#include <QApplication>
#include <QSerialPort>
#include <QSerialPortInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    SerialMonitor x;
    x.show();

    return a.exec();
}
