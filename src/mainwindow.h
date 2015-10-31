#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcgaugewidget.h"
#include <QTimer>


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void createSpeedGauge(QcGaugeWidget* gaugeWidget, int range_minValue, int range_maxValue);


    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void timerHandler();


    void on_pushButtonChangeSpeedGauge_clicked();

    void on_pushButtonStopTimer_clicked();

private:
    Ui::MainWindow *ui;

    QcLabelItem *lab;

    QcLabelItem *lab2;

    QTimer *timer1;

    static int counter;

    static int current_value;
    //new object
    QcGaugeWidget *mySpeedGauge;
    QcNeedleItem *mySpeedNeedle;

    //added from example
    QcGaugeWidget *mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;
};

#endif // MAINWINDOW_H
