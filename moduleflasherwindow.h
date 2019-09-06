#ifndef MODULEFLASHERWINDOW_H
#define MODULEFLASHERWINDOW_H

#include <QMainWindow>
#include "myserial.h"
#include "rrcmoduleflasher.h"
#include <QLabel>
#include <QButtonGroup>
#include <QLineEdit>
#include "moduleflasherwindowsettings.h"
#include "rrccommunication.h"

namespace Ui {
class ModuleFlasherWindow;
}
/**
 * @brief implementations of Class responsible for operating GUI Window for flasher module
 *
 * @author Aleksander Felisiak
 * @date $Date: 2019/08/17 12:22:00 $
 *
 * Contact: olek.felisiak@gmail.com
 *
 * Created on: Saturday Aug 17th 2019
 *
 */
class ModuleFlasherWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ModuleFlasherWindow constructor of the class object
     * @param n_serial passed from the calling object pointer to the actually used serial port
     * @param n_communication passed from the calling object pointer to the actually used comunication protocol
     * @param parent pointer to the calling object from QT standard
     */
    explicit ModuleFlasherWindow(mySerial *n_serial, RRCCommunication *n_communication, QWidget *parent = nullptr);
    /**
     * @brief ModuleFlasherWindow deconstructor of the class object
     */
    ~ModuleFlasherWindow();

private slots:
    /**
     * @brief on_horizontalSlider_flashingPeriod_sliderMoved slot responsible for setting line edit for flashing period when slider under it is moved
     * @param position actuall position of the slider
     */
    void on_horizontalSlider_flashingPeriod_sliderMoved(int position);

    /**
     * @brief on_lineEdit_flashPeriod_textEdited slot responsible for setting position of flashing period slider when text in a line edit was modified
     * @param arg1 parameter cointaining text form of the line edit content
     */
    void on_lineEdit_flashPeriod_textEdited(const QString &arg1);

    /**
     * @brief on_horizontalSlider_timeDeactivation_sliderMoved slot responsible for setting line edit for deactivation time when slider under it is moved
     * @param position actuall position of the slider
     */
    void on_horizontalSlider_timeDeactivation_sliderMoved(int position);

    /**
     * @brief on_lineEdit_timeDeactivation_textEdited slot responsible for setting position of deactivation time slider when text in a line edit was modified
     * @param arg1 parameter cointaining text form of the line edit content
     */
    void on_lineEdit_timeDeactivation_textEdited(const QString &arg1);

    /**
     * @brief on_horizontalSlider_maxTime_sliderMoved slot responsible for setting line edit for maximum activation time when slider under it is moved
     * @param position actuall position of the slider
     */
    void on_horizontalSlider_maxTime_sliderMoved(int position);

    /**
     * @brief on_lineEdit_maxTime_textEdited slot responsible for setting position of deactivation time slider when text in a line edit was modified
     * @param arg1 parameter cointaining text form of the line edit content
     */
    void on_lineEdit_maxTime_textEdited(const QString &arg1);

    /**
     * @brief on_pushButton_AdvencedSettings_clicked slot handling pressing of the advanced setting window, calls ModuleFlasherWindowSettings object
     */
    void on_pushButton_AdvencedSettings_clicked();

    /**
     * @brief fillSerialPorts slot responsible for filling combo box with actually avaliable serial ports
     */
    void fillSerialPorts();

    /**
     * @brief serialPortConnectedInterfaceLockout slot responsible for enabling/disabling part of the interface depending of the status of the serial connection
     * @param status status of the serial port connection
     */
    void serialPortConnectedInterfaceLockout(bool status);

    /**
     * @brief checkAllInputs slot responsible of checking values of all inputs in a inputs configuration section
     */
    void checkAllInputs();
    
    /**
     * @brief on_pushButtonSearch_clicked slot called when Search button is clicked, updates list of the avaliable serial ports
     */
    void on_pushButtonSearch_clicked();

    /**
     * @brief on_pushButtonConnect_clicked slot called when Connect button is clicked, initiates connection to the serial port
     */
    void on_pushButtonConnect_clicked();

    /**
     * @brief on_pushButtonDisconnect_clicked slot called when Disconnect button is clicke, initiates disconnection with a serial port
     */
    void on_pushButtonDisconnect_clicked();

    /**
     * @brief on_pushButton_updateModule_clicked slot called when Update module button is clicked, initiates process of updating parameters in a connected module
     */
    void on_pushButton_updateModule_clicked();

    /**
     * @brief dispalyModuleValues slot responsible for reading all parameters from the module flasher presenting class (RRCModuleFlasher) to be displayed
     */
    void dispalyModuleValues();

    /**
     * @brief on_pushButton_loadModule_clicked slot called to load and display values from the connected module
     */
    void on_pushButton_loadModule_clicked();

private:
    Ui::ModuleFlasherWindow *ui; /**< poinert to the User interface, QT standard */
    ModuleFlasherWindowSettings *advancedSettings; /**< pointer to the advanced settings window object */
    mySerial *serial; /**< pointer to the active serial port */
    RRCModuleFlasher *mflasher; /**< pointer to the object representing flasher module, holding all module parameters */
    RRCCommunication *mcommunication; /**< pointer to the actually used communication protocol */
    QButtonGroup *inputs[6]; /**< array of pointer responsible for simplification of accesing radio buttons for inputs configuration */

    /**
     * @brief SetInputModesDisabled method responsible for disabling inputs configuration when module MODE is set to manual
     */
    void SetInputModesDisabled();

    /**
     * @brief SetInputModesEnabled method responsible for enabling inputs configuration when module MODE is set to automatic
     */
    void SetInputModesEnabled();

    /**
     * @brief displayDefaultValyues method responsible for loading default values for this kind of module
     */
    void displayDefaultValyues(); //TODO: implementation and usage

    /**
     * @brief setLabel method responsible for setting value of the lable below the picture of the module line Serian number
     * @param tag - lable for the parameter for ex. SN for Serial Number
     * @param text - new value of the lable
     * @param label - pointer to the QLable object that is supposed to contain new value
     */
    void setLabel(QString tag, QString text, QLabel *label);
    /**
     * @brief readInputMode method called to check value of the input in a module to set it in a input configuration section
     * @param inputNumber number of the input (0-5)
     */
    void readInputMode(int inputNumber);
    /**
     * @brief groupRadioButtons method called to initiate aray of the pointer to the radioButtonGroups
     */
    void groupRadioButtons();
    /**
     * @brief setMode method responsible for setting mode (from the module memory)
     * @return
     */
    bool setMode();
    /**
     * @brief setLineEditAndSlider set of methods to set value of the lineEdit depending on the type of the input
     * @param lineEdit
     * @param n_value
     */
    void setLineEditAndSlider(QLineEdit *lineEdit, double n_value);
    void setLineEditAndSlider(QLineEdit *lineEdit, float n_value);
    void setLineEditAndSlider(QLineEdit *lineEdit, int n_value);
    void setLineEditAndSlider(QLineEdit *lineEdit, uint8_t n_value);
    void setLineEditAndSlider(QLineEdit *lineEdit, uint16_t n_value);
    /**
     * @brief updateModuleSettings method called to update values in the module representing class with values from the user interface
     */
    void updateModuleSettings();
};

#endif // MODULEFLASHERWINDOW_H
