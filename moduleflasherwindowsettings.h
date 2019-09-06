#ifndef MODULEFLASHERWINDOWSETTINGS_H
#define MODULEFLASHERWINDOWSETTINGS_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include "rrcmoduleflasher.h"

namespace Ui {
class ModuleFlasherWindowSettings;
}
/**
 * @brief The ModuleFlasherWindowSettings class responsible for operation of the module flasher advanced setting window
 * @author Aleksander Felisiak
 * @date $Date: 2019/08/17 12:22:00 $
 *
 * Contact: olek.felisiak@gmail.com
 *
 * Created on: Saturday Aug 17th 2019
 *
 */
class ModuleFlasherWindowSettings : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ModuleFlasherWindowSettings constructor of the class
     * @param flasher pointer to the module representing object, to get acces to representation of module memory of parameters
     * @param parent pointer to the calling object, QT standard
     */
    explicit ModuleFlasherWindowSettings(RRCModuleFlasher *flasher, QWidget *parent = nullptr);
    ~ModuleFlasherWindowSettings();

    /**
     * @brief updateAdvancedSettings method called to update setting values in a module representing object with actual values of the window
     */
    void updateAdvancedSettings();

private:
    Ui::ModuleFlasherWindowSettings *ui; /**< pointer to the GUI interface of the window, QT Standard */
    RRCModuleFlasher *mflasher; /**< pointer to the module representing object */
    QLineEdit *inputActivationDelay[6]; /**< array of pointers for line edit fields, responsible for simplification access to those objects */
    QLineEdit *inputDeactivationDelay[6]; /**< array of pointers for line edit fields, responsible for simplification access to those objects */
    QCheckBox *inputActiveState[6]; /**< array of pointers for check box fields, responsible for simplification access to those objects */

    /**
     * @brief setArrays method called to initiate arrays of pointers simplifinig access to the data in GUI
     */
    void setArrays();
    /**
     * @brief displayModuleValues method called to dispaly values from the module representation object
     */
    void displayModuleValues();

public slots:
    /**
     * @brief setInputMode slot responsible for enabling/disabling part of the interface dependent from the value of the input mode parameter from the ModuleFlasherWindow/Module representation
     * @param status - mode value
     */
    void setInputMode(bool status);

private slots:
    /**
     * @brief on_buttonBox_rejected slot called when user discarde changes by closing window or clicking cancel
     */
    void on_buttonBox_rejected();
};

#endif // MODULEFLASHERWINDOWSETTINGS_H
