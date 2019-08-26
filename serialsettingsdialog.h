#ifndef SERIALSETTINGSDIALOG_H
#define SERIALSETTINGSDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include "myserial.h"

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
    explicit SerialSettingsDialog(QWidget *parent = nullptr);
    ~SerialSettingsDialog();

    mySerial *currentSettings;
    //mySerial settings() const;
    void externalSerialIndexChange(int idx);

signals:
     void serialIndexChanged(int idx);

private slots:
    void showPortInfo(int idx);
    void apply();

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private:
    Ui::SerialSettingsDialog *ui = nullptr;

    QIntValidator *intValidator = nullptr;
};

#endif // SERIALSETTINGSDIALOG_H
