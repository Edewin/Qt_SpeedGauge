#-------------------------------------------------
#
# Project created by QtCreator 2015-10-29T21:42:51
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lsfml-graphics -lsfml-window -lsfml-system

TARGET = testGaugeWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcgaugewidget.cpp

HEADERS  += mainwindow.h \
    qcgaugewidget.h \
    delayclass.h

FORMS    += mainwindow.ui
