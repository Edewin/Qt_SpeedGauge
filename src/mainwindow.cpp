#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "delayclass.h"
#include <QTimer>


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
    mSpeedGauge->addDegrees(65)->setValueRange(0,80);
    mSpeedGauge->addColorBand(50);

    mSpeedGauge->addValues(80)->setValueRange(0,80);

    mSpeedGauge->addLabel(70)->setText("Km/h");
    lab = mSpeedGauge->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0,80);
    mSpeedGauge->addBackground(4);
    mSpeedGauge->addGlass(88);

    ui->verticalLayout->addWidget(mSpeedGauge);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    mSpeedNeedle->setCurrentValue(value);

    QString speedValueString;
    speedValueString = speedValueString.sprintf("%d",value);
    lab->setText(speedValueString);
}


void MainWindow::on_pushButtonChangeSpeedGauge_clicked()
{
    for(int i=0; i<=80; i++)
    {
        Delay::msleep(100);
        mSpeedNeedle->setCurrentValue(i);

    }
}

void MainWindow::timerHandler()
{
    // timer handler


}
