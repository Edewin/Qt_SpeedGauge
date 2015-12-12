#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcgaugewidget.h"
#include <QTimer>
#include <QMessageBox>
#include <QByteArray>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void createSpeedGauge(QcGaugeWidget* gaugeWidget, int range_minValue, int range_maxValue);

    qreal normalizeJoystick(qreal inputValue);


    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void timerHandler();

    void handlerReadSerial();

    void on_pushButtonChangeSpeedGauge_clicked();

    void on_pushButtonStopTimer_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_SendSerial_clicked();

private:
    QMessageBox msgbox;

    QSerialPort *serial;
    QSerialPortInfo availablePorts;
    QByteArray bufferSerialRead;

    Ui::MainWindow *ui;

    QString portAvailable;

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
