#include "moduleflasherwindowsettings.h"
#include "ui_moduleflasherwindowsettings.h"
#include <QtDebug>

ModuleFlasherWindowSettings::ModuleFlasherWindowSettings(RRCModuleFlasher *flasher, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleFlasherWindowSettings),
    mflasher(flasher)
{
    ui->setupUi(this);
     setArrays();

    displayModuleValues();
}

ModuleFlasherWindowSettings::~ModuleFlasherWindowSettings()
{
    delete ui;
    for (int i = 0; i < 6;++i) {
        delete inputActiveState[i];
        delete inputActivationDelay[i];
        delete inputDeactivationDelay[i];
    }

}

void ModuleFlasherWindowSettings::updateAdvancedSettings()
{
    mflasher->gateDelay(uint8_t(ui->GateDrop->text().toInt()));
    for (int i = 0; i < 6;++i)
    {
        mflasher->activeInputState(i, inputActiveState[i]->isChecked());
        mflasher->inputActivationDelay(i, uint8_t(inputActivationDelay[i]->text().toInt()));
        mflasher->inputDeactivationDelay(i, uint8_t(inputDeactivationDelay[i]->text().toInt()));
    }
}

void ModuleFlasherWindowSettings::setArrays()
{
    inputActiveState[0] = ui->checkBoxActHigh1;
    inputActiveState[1] = ui->checkBoxActHigh2;
    inputActiveState[2] = ui->checkBoxActHigh3;
    inputActiveState[3] = ui->checkBoxActHigh4;
    inputActiveState[4] = ui->checkBoxActHigh5;
    inputActiveState[5] = ui->checkBoxActHigh6;

    inputActivationDelay[0] = ui->lineEditActDel1;
    inputActivationDelay[1] = ui->lineEditActDel2;
    inputActivationDelay[2] = ui->lineEditActDel3;
    inputActivationDelay[3] = ui->lineEditActDel4;
    inputActivationDelay[4] = ui->lineEditActDel5;
    inputActivationDelay[5] = ui->lineEditActDel6;

    inputDeactivationDelay[0] = ui->lineEditDctDel1;
    inputDeactivationDelay[1] = ui->lineEditDctDel2;
    inputDeactivationDelay[2] = ui->lineEditDctDel3;
    inputDeactivationDelay[3] = ui->lineEditDctDel4;
    inputDeactivationDelay[4] = ui->lineEditDctDel5;
    inputDeactivationDelay[5] = ui->lineEditDctDel6;

}

void ModuleFlasherWindowSettings::displayModuleValues()
{
    ui->GateDrop->setText(QString::number(mflasher->gateDelay()));
    for (int i = 0; i < 6; ++i) {
        inputActiveState[i]->setChecked(mflasher->activeInputState(i));
        inputActivationDelay[i]->setText(QString::number(mflasher->inputActivationDelay(i)));
        inputDeactivationDelay[i]->setText(QString::number(mflasher->inputDeactivationDelay(i)));
    }
}

void ModuleFlasherWindowSettings::setInputMode(bool status)
{
    ui->lableIN1->setEnabled(status);
    ui->lableIN2->setEnabled(status);
    ui->lableIN3->setEnabled(status);
    ui->lableIN4->setEnabled(status);
    ui->lableIN5->setEnabled(status);
    ui->lableIN6->setEnabled(status);

    ui->labelActivationStatus->setEnabled(status);
    ui->labelInputActivationDelay->setEnabled(status);
    ui->lableInputDeactivationDelay->setEnabled(status);

    ui->lineEditActDel1->setEnabled(status);
    ui->lineEditActDel2->setEnabled(status);
    ui->lineEditActDel3->setEnabled(status);
    ui->lineEditActDel4->setEnabled(status);
    ui->lineEditActDel5->setEnabled(status);
    ui->lineEditActDel6->setEnabled(status);

    ui->lineEditDctDel1->setEnabled(status);
    ui->lineEditDctDel2->setEnabled(status);
    ui->lineEditDctDel3->setEnabled(status);
    ui->lineEditDctDel4->setEnabled(status);
    ui->lineEditDctDel5->setEnabled(status);
    ui->lineEditDctDel6->setEnabled(status);

    ui->checkBoxActHigh1->setEnabled(status);
    ui->checkBoxActHigh2->setEnabled(status);
    ui->checkBoxActHigh3->setEnabled(status);
    ui->checkBoxActHigh4->setEnabled(status);
    ui->checkBoxActHigh5->setEnabled(status);
    ui->checkBoxActHigh6->setEnabled(status);
}

void ModuleFlasherWindowSettings::on_buttonBox_rejected()
{
    displayModuleValues();
}
