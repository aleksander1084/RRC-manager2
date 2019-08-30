#ifndef MODULEFLASHERWINDOW_H
#define MODULEFLASHERWINDOW_H

#include <QMainWindow>
#include "myserial.h"

namespace Ui {
class ModuleFlasherWindow;
}

class ModuleFlasherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModuleFlasherWindow(mySerial *n_serial, QWidget *parent = nullptr);
    ~ModuleFlasherWindow();

private slots:
    void on_horizontalSlider_flashingPeriod_sliderMoved(int position);


    void on_lineEdit_flashPeriod_textEdited(const QString &arg1);

    void on_horizontalSlider_timeDeactivation_sliderMoved(int position);

    void on_lineEdit_timeDeactivation_textEdited(const QString &arg1);

    void on_horizontalSlider_maxTime_sliderMoved(int position);

    void on_lineEdit_maxTime_textEdited(const QString &arg1);

    void on_pushButton_AdvencedSettings_clicked();

    void fillSerialPorts();
    
private:
    Ui::ModuleFlasherWindow *ui;
    mySerial *serial;
    void SetInputModesDisabled();
    void SetInputModesEnabled();
    void serialPortConnectedInterfaceLockout(bool status);
};

#endif // MODULEFLASHERWINDOW_H
