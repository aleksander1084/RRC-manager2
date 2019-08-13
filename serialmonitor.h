#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QWidget>

#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {


class SerialMonitor;
}

class SerialMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit SerialMonitor(QWidget *parent = nullptr);
    void ListAvaliablePorts();
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

private:
    void AddToLogs(QString message, QString direction);
    void sendMessageToSerialPort(QString message);
    void sendCommandLineToSerialPort();
    Ui::SerialMonitor *ui;
};

#endif // SERIALMONITOR_H
