#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "delayclass.h"
#include <QTimer>

#define MIN_VALUE 0
#define MAX_VALUE 100


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSpeedGauge = new QcGaugeWidget;
    QcBackgroundItem * contour = mSpeedGauge->addBackground(96);
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

    ui->verticalLayout->addWidget(mSpeedGauge);

    //timer zone

    timer1 = new QTimer(this);

    connect(timer1, SIGNAL(timeout()),this,SLOT(timerHandler()));



}

/*initialize static variables*/

int MainWindow::counter = 0;
int MainWindow::current_value = 0;

/************************************/

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    mSpeedNeedle->setCurrentValue(value);
    MainWindow::current_value = value;

    QString speedValueString;
    speedValueString = speedValueString.sprintf("%d",MainWindow::current_value);
    lab->setText(speedValueString);
}


void MainWindow::on_pushButtonChangeSpeedGauge_clicked()
{
    timer1->start(100);
}

void MainWindow::timerHandler()
{
    // timer handler
    MainWindow::counter++;

<<<<<<< HEAD
=======

>>>>>>> 6735d5ec761f1d6e2117a3398df732f09719f312

    if(counter > MAX_VALUE)
    {
        counter = MIN_VALUE;
    }
    mSpeedNeedle->setCurrentValue(MainWindow::counter);
    MainWindow::current_value = MainWindow::counter;

    QString speedValueString;
    speedValueString = speedValueString.sprintf("%d",MainWindow::current_value);
    lab->setText(speedValueString);
}



void MainWindow::on_pushButtonStopTimer_clicked()
{
    timer1->stop();
}
