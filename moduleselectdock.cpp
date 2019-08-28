#include "moduleselectdock.h"
#include "ui_moduleselectdock.h"


ModuleSelectDock::ModuleSelectDock(mySerial *n_serial, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleSelectDock),
    serial(n_serial)
{
    ui->setupUi(this);
}

ModuleSelectDock::~ModuleSelectDock()
{
    delete ui;
    delete mWindow;
}

void ModuleSelectDock::on_pushButtonFlasher_clicked()
{
    if(mWindow != nullptr)
    {
        delete mWindow;
    }
    mWindow = new ModuleFlasherWindow(serial);
    mWindow->show();
}
