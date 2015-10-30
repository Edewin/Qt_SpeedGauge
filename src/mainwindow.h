#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcgaugewidget.h"


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void timerHandler();


    void on_pushButtonChangeSpeedGauge_clicked();

private:
    Ui::MainWindow *ui;

    QcLabelItem *lab;
    //added from example
    QcGaugeWidget *mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;
};

#endif // MAINWINDOW_H
