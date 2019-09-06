#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "testwidget.h"
#include "serialmonitor.h"
#include <QMenu>
#include "myserial.h"
#include "moduleselectdock.h"
#include "rrccommunication.h"
#include "rrcmoduleautodetect.h"

namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class implements a main window of the QT aplication, based fully on the QT documentation and standard
 *
 * @author Aleksander Felisiak
 * @date $Date: 2019/08/17 12:22:00 $
 *
 * Contact: olek.felisiak@gmail.com
 *
 * Created on: Saturday Aug 17th 2019
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow constructor of the main window
     * @param parent - parameter desctibing object that called main window, because it is called ridectly in a main program this parameter is never used, but is part of a QT standard
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;/**< pointer to the GUI object*/
    TestWidget *testWidget; /**< pointer for object ocated in a dock widget */
    SerialMonitor *serialMonitor;/**< pointer for object ocated in a dock widget */
    ModuleSelectDock *mselectDock;/**< pointer for object ocated in a dock widget */
    QMenu *viewMenu;/**< pointer for top menu */
    mySerial *serial;/**< pointer for serial port control object */
    RRCCommunication *communication;/**< pointer for communuication object responsible for interpreating messages */
    RRCModuleAutoDetect *mautoDetect;/**< pointer for the object that is responsible for runing automatic detection of the new connected devices and checking is it a functional module*/

    void topMenu();/**< method responsible for preaparing top menu*/
    void setDocks();/**< method responsible for preaparing dock widgets*/
    QMenu *createPopupMenu();/**< overload of a standard QT QMenu virtual function responsible for creating popUp menus*/
};

#endif // MAINWINDOW_H
