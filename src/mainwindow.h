#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcgaugewidget.h"
#include <QTimer>
#include <QMessageBox>


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
    QMessageBox msgbox;

    Ui::MainWindow *ui;

    QcLabelItem *lab;

    QString textLabel;

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
