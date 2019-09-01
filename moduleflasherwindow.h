#ifndef MODULEFLASHERWINDOW_H
#define MODULEFLASHERWINDOW_H

#include <QMainWindow>
#include "myserial.h"
#include "rrcmoduleflasher.h"
#include <QLabel>
#include <QButtonGroup>
#include <QLineEdit>
#include "moduleflasherwindowsettings.h"

//TODO: Doxygen

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

    void serialPortConnectedInterfaceLockout(bool status);

    void checkAllInputs();
    
    void on_pushButtonSearch_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

    void on_pushButton_updateModule_clicked();

private:
    Ui::ModuleFlasherWindow *ui;
    ModuleFlasherWindowSettings *advancedSettings;
    mySerial *serial;
    RRCModuleFlasher *mflasher;
    QButtonGroup *inputs[6];
    void SetInputModesDisabled();
    void SetInputModesEnabled();
    void dispalyModuleValues();
    void displayDefaultValyues();
    void setLabel(QString tag, QString text, QLabel *label);
    void readInputMode(int inputNumber);
    void groupRadioButtons();
    bool setMode();
    void setLineEditAndSlider(QLineEdit *lineEdit, double n_value);
    void setLineEditAndSlider(QLineEdit *lineEdit, float n_value);
    void setLineEditAndSlider(QLineEdit *lineEdit, int n_value);
    void setLineEditAndSlider(QLineEdit *lineEdit, uint8_t n_value);
    void setLineEditAndSlider(QLineEdit *lineEdit, uint16_t n_value);
    void updateModuleSettings();




};

#endif // MODULEFLASHERWINDOW_H
