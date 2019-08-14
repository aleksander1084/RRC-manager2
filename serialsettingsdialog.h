#ifndef SERIALSETTINGSDIALOG_H
#define SERIALSETTINGSDIALOG_H

#include <QDialog>
#include <QSerialPort>

QT_BEGIN_NAMESPACE

namespace Ui {
class SerialSettingsDialog;
}

class QIntValidator;

QT_END_NAMESPACE

class SerialSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
        int idx;
    };

    explicit SerialSettingsDialog(QWidget *parent = nullptr);
    ~SerialSettingsDialog();

    Settings currentSettings;
    Settings settings() const;
    void externalSerialIndexChange(int idx);

signals:
     void serialIndexChanged(int idx);

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private:
    Ui::SerialSettingsDialog *ui = nullptr;

    QIntValidator *intValidator = nullptr;
};

#endif // SERIALSETTINGSDIALOG_H
