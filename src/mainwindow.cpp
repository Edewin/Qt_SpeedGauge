#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcgaugewidget.h"

#include "delayclass.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <SFML/Window.hpp>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

#define MIN_VALUE 0
#define MAX_VALUE 70


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);



    //serial port info
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->plainTextEdit->appendPlainText(info.portName());
        portAvailable = info.portName(); //just checking the concept --> must implement a much robust method to use Serial Port
        ui->comboBox->addItem(portAvailable);
    }

    //ui->plainTextEdit->appendPlainText();


    sf::Joystick::update();

//    if(sf::Joystick::isConnected(0))
//    {
//        //joystick number 0 is connected
//        msgbox.setText("joystick 0 is connected");
//        msgbox.exec();

//    }
//    else
//    {
//        qDebug()<<"joystick 0 is not connected";
//    }

    serial = new QSerialPort(this);
   // serial->setPortName("dev/pts/2");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->open(QSerialPort::ReadOnly);
   // availablePorts = new QSerialPortInfo();



    mSpeedGauge = new QcGaugeWidget(this);
    mSpeedNeedle = new QcNeedleItem(this);

    mySpeedGauge = new QcGaugeWidget(this);
    mySpeedNeedle = new QcNeedleItem(this);

    lab = new QcLabelItem(this);
    lab2 = new QcLabelItem(this);


    createSpeedGauge(mSpeedGauge, MIN_VALUE, MAX_VALUE);

    lab = mSpeedGauge->addLabel(40);
    lab->setText("0");

    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(0xFE2E9A);

    mSpeedNeedle->setNeedle(QcNeedleItem::FeatherNeedle);

    mSpeedNeedle->setValueRange(MIN_VALUE,MAX_VALUE);
    mSpeedGauge->addBackground(4);

    mSpeedGauge->addGlass(0.1);

    createSpeedGauge(mySpeedGauge, MIN_VALUE, MAX_VALUE);

    lab2 = mySpeedGauge->addLabel(40);
    lab2->setText("0");

    mySpeedNeedle = mySpeedGauge->addNeedle(60);
    mySpeedNeedle->setLabel(lab2);
    mySpeedNeedle->setColor(0xFF8000);
    mySpeedNeedle->setNeedle(QcNeedleItem::FeatherNeedle);
    mySpeedNeedle->setValueRange(MIN_VALUE,MAX_VALUE);
    mySpeedGauge->addBackground(4);
  //  mySpeedGauge->addGlass(89)->setPosition(30);


    ui->horizontalLayout->addWidget(mSpeedGauge);
    ui->horizontalLayout->addWidget(mySpeedGauge);


    //timer zone

    timer1 = new QTimer(this);

    connect(timer1, SIGNAL(timeout()),this,SLOT(timerHandler()));

    // connect serial port with slots :)
    connect(serial,SIGNAL(readyRead()),this,SLOT(handlerReadSerial()));



}

/***********************************************
 *      Serial handler
*********************************************/

void MainWindow::handlerReadSerial()
{
    bufferSerialRead.append(serial->readAll());
   // qDebug()<< bufferSerialRead;
    ui->plainTextEdit->appendPlainText( QString::fromStdString(bufferSerialRead.toStdString()) );
}

/************************************/


/*initialize static variables*/

int MainWindow::counter = 0;
int MainWindow::current_value = 0;

/************************************/

MainWindow::~MainWindow()
{
    if(serial->isOpen())
    {
        serial->close();
    }
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    mSpeedNeedle->setCurrentValue(value);
    mySpeedNeedle->setCurrentValue(value);
    MainWindow::current_value = value;

    QString speedValueString;
    speedValueString = speedValueString.sprintf("%d",MainWindow::current_value +40);
    lab->setText(speedValueString);
    speedValueString = speedValueString.sprintf("%d",MainWindow::current_value);
    lab2->setText(speedValueString);
}


void MainWindow::on_pushButtonChangeSpeedGauge_clicked()
{
    timer1->start(40);

  //  msgbox.setText("Timer1 has been released to space :D");
  //  msgbox.exec();
}

void MainWindow::timerHandler()
{
    // timer handler
    MainWindow::counter++;
    MainWindow::current_value++;

    if(MainWindow::current_value > MAX_VALUE)
    {
        MainWindow::current_value= MIN_VALUE;
    }
    mSpeedNeedle->setCurrentValue(-sf::Joystick::getAxisPosition(0,sf::Joystick::X));

    sf::Joystick::update();

    qreal myLeftJoystick = sf::Joystick::getAxisPosition(0,sf::Joystick::Y);
    qreal myRightJoystick = sf::Joystick::getAxisPosition(0,sf::Joystick::U);

    myRightJoystick = normalizeJoystick(myRightJoystick);


    ui->progressBar->setValue((int)-myLeftJoystick  );

    if(serial->isOpen())
    {
        QString localTxBuf;
        int rJoy = (int) (myRightJoystick * 10);

        if(rJoy < 2)
        {
            rJoy = 2;
        }
        else if (rJoy > 8)
        {
            rJoy = 8;
        }

        localTxBuf.sprintf("%d", rJoy);

        qDebug()<< localTxBuf;

        serial->write(localTxBuf.toUtf8());

        localTxBuf.clear();
    }

    textLabel = textLabel.sprintf("X: %f, Y: %f", myLeftJoystick, myRightJoystick );

    ui->label->setText(textLabel);
    mySpeedNeedle->setCurrentValue(-sf::Joystick::getAxisPosition(0,sf::Joystick::Y));
  //  MainWindow::current_value = MainWindow::counter;

    QString speedValueString;
    speedValueString = speedValueString.sprintf("%d",MainWindow::current_value + 40);
    lab->setText(speedValueString);
    speedValueString = speedValueString.sprintf("%d",MainWindow::current_value);
    lab2->setText(speedValueString);
}



void MainWindow::on_pushButtonStopTimer_clicked()
{
    timer1->stop();
}

void MainWindow::createSpeedGauge(QcGaugeWidget* gaugeWidget,  int range_minValue, int range_maxValue)
{
    QcBackgroundItem * contour = gaugeWidget->addBackground(99);
    contour->clearrColors();
    contour->addColor(0.1,Qt::black);
    contour->addColor(0.5,Qt::darkGray);
    contour->addColor(0.9,Qt::black);


    QcBackgroundItem *bkg1 = gaugeWidget->addBackground(94);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
  //  bkg1->addColor(0.4,Qt::white);
  //  bkg1->addColor(0.5,Qt::darkYellow);
  //  bkg1->addColor(0.6,Qt::white);
    bkg1->addColor(1.0,Qt::black);

    QcBackgroundItem *bkg2 = gaugeWidget->addBackground(15);
    bkg2->clearrColors();
    bkg2->addColor(0.5,Qt::darkGray);
  //  bkg2->addColor(1.0, Qt::darkYellow);
    bkg2->addColor(0.1,Qt::black);

   // gaugeWidget->addArc(70)->setColor(0x00FF00);
    gaugeWidget->addArc(28)->setColor(Qt::darkBlue);

    QcDegreesItem* degrees;

    degrees = gaugeWidget->addDegrees(90);
    degrees->setValueRange(range_minValue,range_maxValue);
    degrees->setStep(5);
    degrees->setColor(Qt::white);
    //gaugeWidget->addColorBand(95);

    QcValuesItem * values;
    values = gaugeWidget->addValues(68);
    values->setValueRange(range_minValue,range_maxValue);
    values->setColor(Qt::white);

    gaugeWidget->addLabel(70)->setText("Km/h");

}

qreal MainWindow::normalizeJoystick(qreal inputValue)
{
    return ( 1.00 - ( (inputValue + 100.00) / 200.00 ) );

}

void MainWindow::on_pushButton_clicked()
{
    // serial connect
    serial->setPortName(portAvailable);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->open(QIODevice::ReadWrite);
    if(serial->isOpen())
    {
        QMessageBox msg;
        msg.setText("serial is open");
        qDebug()<< "serial is open";
        msg.exec();
    }
    else
    {
        qDebug() << "serial is not open";
    }

}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(true);
    qDebug() << "combo box is: "<< arg1 ;
    portAvailable = arg1;
}

void MainWindow::on_pushButton_SendSerial_clicked()
{
    QString txString;
    txString = ui->serialText->text();

    serial->write(txString.toUtf8());
}
