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
    }


    //ui->plainTextEdit->appendPlainText();


    sf::Joystick::update();

    if(sf::Joystick::isConnected(0))
    {
        //joystick number 0 is connected
        msgbox.setText("joystick 0 is connected");
        msgbox.exec();

    }
    else
    {
        qDebug()<<"joystick 0 is not connected";
    }

    serial = new QSerialPort(this);
    serial->setPortName("dev/pts/2");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->open(QSerialPort::ReadOnly);
   // availablePorts = new QSerialPortInfo();



    mSpeedGauge = new QcGaugeWidget(this);
    mSpeedNeedle = new QcNeedleItem(this);

    mySpeedGauge = new QcGaugeWidget(this);
    mySpeedNeedle = new QcNeedleItem(this);

    lab = new QcLabelItem(this);
    lab2 = new QcLabelItem(this);

   /* QcBackgroundItem * contour = mSpeedGauge->addBackground(96);
    contour->clearrColors();
    contour->addColor(0.1,Qt::white);
    contour->addColor(0.5,Qt::red);
    contour->addColor(0.9,Qt::white);
   // mSpeedGauge->addBackground(100)->addColor(0.2,Qt::red);

    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::darkBlue);
    bkg1->addColor(0.4,Qt::white);
    bkg1->addColor(0.9,Qt::darkBlue);

    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.2,Qt::red);
    bkg2->addColor(0.7, Qt::yellow);
    bkg2->addColor(1.0,Qt::darkGreen);

    mSpeedGauge->addArc(55);
    mSpeedGauge->addDegrees(65)->setValueRange(MIN_VALUE,MAX_VALUE);
    mSpeedGauge->addColorBand(50);

    mSpeedGauge->addValues(80)->setValueRange(MIN_VALUE,MAX_VALUE);

    mSpeedGauge->addLabel(70)->setText("Km/h");

    lab = mSpeedGauge->addLabel(40);
    lab->setText("0");

    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(MIN_VALUE,MAX_VALUE);
    mSpeedGauge->addBackground(4);
    mSpeedGauge->addGlass(0.1);
*/

    createSpeedGauge(mSpeedGauge, MIN_VALUE + 40, MAX_VALUE+40);

    lab = mSpeedGauge->addLabel(40);
    lab->setText("0");

    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(0xFE2E9A);

    mSpeedNeedle->setNeedle(QcNeedleItem::DiamonNeedle);

    mSpeedNeedle->setValueRange(MIN_VALUE,MAX_VALUE);
    mSpeedGauge->addBackground(4);
    mSpeedGauge->addGlass(0.1);

    createSpeedGauge(mySpeedGauge, MIN_VALUE, MAX_VALUE);

    lab2 = mySpeedGauge->addLabel(40);
    lab2->setText("0");

    mySpeedNeedle = mySpeedGauge->addNeedle(60);
    mySpeedNeedle->setLabel(lab2);
    mySpeedNeedle->setColor(Qt::darkBlue);
    mySpeedNeedle->setNeedle(QcNeedleItem::AttitudeMeterNeedle);
    mySpeedNeedle->setValueRange(MIN_VALUE,MAX_VALUE);
    mySpeedGauge->addBackground(4);
    mySpeedGauge->addGlass(59)->setPosition(2);


    ui->horizontalLayout->addWidget(mSpeedGauge);
    ui->horizontalLayout->addWidget(mySpeedGauge);
   // lab->setText("123");

   // ui->gridLayout_2->addWidget(mSpeedGauge);

    //timer zone

    timer1 = new QTimer(this);

    connect(timer1, SIGNAL(timeout()),this,SLOT(timerHandler()));

    // connect serial port with slots :)
    connect(serial,SIGNAL(readyRead()),this,SLOT(handlerReadSerial()));



}

//serial handler

void MainWindow::handlerReadSerial()
{
    bufferSerialRead.append(serial->readAll());
   // qDebug()<< bufferSerialRead;
    ui->plainTextEdit->appendPlainText( QString::fromStdString(bufferSerialRead.toStdString()) );
}

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
    serial->setPortName(portAvailable);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->open(QIODevice::ReadOnly);
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
    textLabel = textLabel.sprintf("X: %f, Y: %f",sf::Joystick::getAxisPosition(0,sf::Joystick::X),
                                  sf::Joystick::getAxisPosition(0,sf::Joystick::Y));
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
    bkg1->addColor(0.4,Qt::white);
  //  bkg1->addColor(0.5,Qt::darkYellow);
    bkg1->addColor(0.6,Qt::white);
    bkg1->addColor(1.0,Qt::black);

    QcBackgroundItem *bkg2 = gaugeWidget->addBackground(28);
    bkg2->clearrColors();
    bkg2->addColor(0.5,Qt::white);
  //  bkg2->addColor(1.0, Qt::darkYellow);
    bkg2->addColor(0.1,Qt::darkYellow);

   // gaugeWidget->addArc(70)->setColor(0x00FF00);
    gaugeWidget->addArc(28)->setColor(Qt::darkBlue);
    gaugeWidget->addDegrees(90)->setValueRange(range_minValue,range_maxValue);
   // gaugeWidget->addColorBand(35);

    gaugeWidget->addValues(65)->setValueRange(range_minValue,range_maxValue);

    gaugeWidget->addLabel(70)->setText("Km/h");

}
