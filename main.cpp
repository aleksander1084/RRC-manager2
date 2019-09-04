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
    return a.exec();
}
