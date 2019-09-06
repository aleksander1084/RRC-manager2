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
/**
 * @brief The SerialSettingsDialog class defines dialog with setting of the serial port configuration
 * @author Aleksander Felisiak
 * @date $Date: 2019/08/17 12:22:00 $
 *
 * Contact: olek.felisiak@gmail.com
 *
 * Created on: Monday Aug 12th 2019
 */
class SerialSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief SerialSettingsDialog object constructor
     * @param parent pointer to the calling object,
     */
    explicit SerialSettingsDialog(QWidget *parent = nullptr);
    ~SerialSettingsDialog();

    mySerial *currentSettings; /**< pointer to the active serial port */
    //mySerial settings() const;
    void externalSerialIndexChange(int idx);

signals:
     //void serialIndexChanged(int idx);

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
