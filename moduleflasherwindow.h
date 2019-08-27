#ifndef MODULEFLASHERWINDOW_H
#define MODULEFLASHERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ModuleFlasherWindow;
}

class ModuleFlasherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModuleFlasherWindow(QWidget *parent = nullptr);
    ~ModuleFlasherWindow();

private slots:
    void on_horizontalSlider_flashingPeriod_sliderMoved(int position);


    void on_lineEdit_flashPeriod_textEdited(const QString &arg1);

    void on_horizontalSlider_timeDeactivation_sliderMoved(int position);

    void on_lineEdit_timeDeactivation_textEdited(const QString &arg1);

    void on_horizontalSlider_maxTime_sliderMoved(int position);

    void on_lineEdit_maxTime_textEdited(const QString &arg1);

    void on_pushButton_AdvencedSettings_clicked();
    
private:
    Ui::ModuleFlasherWindow *ui;
    void SetInputModesDisabled();
    void SetInputModesEnabled();
};

#endif // MODULEFLASHERWINDOW_H
