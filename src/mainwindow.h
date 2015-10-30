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

    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void timerHandler();


    void on_pushButtonChangeSpeedGauge_clicked();

    void on_pushButtonStopTimer_clicked();

private:
    Ui::MainWindow *ui;

    QcLabelItem *lab;

    QTimer *timer1;

    static int counter;

    //added from example
    QcGaugeWidget *mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;
};

#endif // MAINWINDOW_H
