#include "moduleselectdock.h"
#include "ui_moduleselectdock.h"


ModuleSelectDock::ModuleSelectDock(mySerial *n_serial, RRCCommunication *n_communication, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleSelectDock),
    serial(n_serial),
    communication(n_communication)
{
    ui->setupUi(this);
}

ModuleSelectDock::~ModuleSelectDock()
{
    delete ui;
    ui = nullptr;
}

void ModuleSelectDock::on_pushButtonFlasher_clicked()
{
    mWindow = new ModuleFlasherWindow(serial, communication, this);
    mWindow->setAttribute(Qt::WA_DeleteOnClose);
    mWindow->show();
}
