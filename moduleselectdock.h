#ifndef MODULESELECTDOCK_H
#define MODULESELECTDOCK_H

#include <QWidget>
#include "myserial.h"
#include "moduleflasherwindow.h"
#include "rrccommunication.h"

namespace Ui {
class ModuleSelectDock;
}
/**
 * @brief The ModuleSelectDock class representation of a dock window (section of the main window) that contains buttons to call windows for specific kinds of modules
 */
class ModuleSelectDock : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ModuleSelectDock object constructor
     * @param n_serial pointer to the active serial port
     * @param n_communication pointer to actually used communication protocol
     * @param parent pointer to the object calling this object to be created, QT standard
     */
    explicit ModuleSelectDock(mySerial *n_serial, RRCCommunication *n_communication, QWidget *parent = nullptr);
    ~ModuleSelectDock();

public slots:
    /**
     * @brief checkAutomaticalyDetectedModule slot called to check is automaticaly detected module recognizable
     */
    void checkAutomaticalyDetectedModule();

private slots:
    /**
     * @brief on_pushButtonFlasher_clicked slot called when Flasher button is clicked
     */
    void on_pushButtonFlasher_clicked();

    /**
     * @brief checkAutomaticalyDetectedModuleSN slot called when Serial number of the automaticaly detected module will be returned to select next actions to take
     * @param sections output of the serial number message processing
     */
    void checkAutomaticalyDetectedModuleSN(QStringList sections);

    /**
     * @brief mWindowWasRejected slot called when window representing module is closed
     */
    void mWindowWasRejected();

    /**
     * @brief on_pushButtonMW_clicked slot called when Microwave button is clicked
     */
    void on_pushButtonMW_clicked(); //TODO: implementation of the MW window

    void on_pushButtonLidar_clicked();//TODO: implementation of the LIdar window

private:
    Ui::ModuleSelectDock *ui;/**<pointer to the GUI, QT standard */
    mySerial *serial; /**<pointer to the actually selected serial port */
    RRCCommunication *communication; /**<pointer to the actually selected communication protocol */
    QDialog *mWindow = nullptr; /**<pointer to the children window with module configuration */
    int automaticConnectionsTries = 0; /**<counter for autpomatic connection tries*/
};

#endif // MODULESELECTDOCK_H
