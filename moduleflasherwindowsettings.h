#ifndef MODULEFLASHERWINDOWSETTINGS_H
#define MODULEFLASHERWINDOWSETTINGS_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include "rrcmoduleflasher.h"

namespace Ui {
class ModuleFlasherWindowSettings;
}

class ModuleFlasherWindowSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ModuleFlasherWindowSettings(RRCModuleFlasher *flasher, QWidget *parent = nullptr);
    ~ModuleFlasherWindowSettings();
    void updateAdvancedSettings();

private:
    Ui::ModuleFlasherWindowSettings *ui;
    RRCModuleFlasher *mflasher;
    QLineEdit *inputActivationDelay[6];
    QLineEdit *inputDeactivationDelay[6];
    QCheckBox *inputActiveState[6];

    void setArrays();
    void displayModuleValues();

public slots:
    void setInputMode(bool status);

private slots:
    void on_buttonBox_rejected();
};

#endif // MODULEFLASHERWINDOWSETTINGS_H
