#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T22:10:00
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlowFreeGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startwidget.cpp \
    aboutwidget.cpp \
    choosewidget.cpp \
    playwidget.cpp

HEADERS  += mainwindow.h \
    startwidget.h \
    aboutwidget.h \
    choosewidget.h \
    stdafx.h \
    playwidget.h

FORMS    += mainwindow.ui \
    startwidget.ui \
    aboutwidget.ui \
    choosewidget.ui \
    playwidget.ui

RESOURCES += \
    resourse.qrc
