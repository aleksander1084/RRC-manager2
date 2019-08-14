#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QWidget>

#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "serialsettingsdialog.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace Ui {


class SerialMonitor;
}

class SerialMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit SerialMonitor(QWidget *parent = nullptr);
    void ListAvaliablePorts();
    void serialPortConnectedInterfaceLockout(bool status);
    void externalSerialIndexChanger(int index);
    QSerialPort *serialPort;
    ~SerialMonitor();

private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

    void readFromSerialPort();

    void on_pushButtonSendCommand_clicked();

    void on_lineEditCommandLine_returnPressed();

    void on_pushButtonClearLog_clicked();

    void on_comboBoxPorts_currentIndexChanged(int index);

    void on_pushButtonSettings_clicked();

private:
    void AddToLogs(QString message, QString direction);
    void sendMessageToSerialPort(QString message);
    void sendCommandLineToSerialPort();
    Ui::SerialMonitor *ui = nullptr;
    QLabel *serialStatus = nullptr;
    SerialSettingsDialog *serialSettings = nullptr;
    QSerialPort *serial = nullptr;
};

#endif // SERIALMONITOR_H
