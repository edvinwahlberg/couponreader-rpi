#-------------------------------------------------
#
# Project created by QtCreator 2019-03-07T09:38:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = couponreader-raspi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    serialhandler.cpp \
    readingsmodel.cpp \
    sensorreadingswidget.cpp \
    mechanicaltestingwidget.cpp

HEADERS += \
        mainwindow.h \
    serialhandler.h \
    readingsmodel.h \
    sensorreadingswidget.h \
    mechanicaltestingwidget.h

FORMS += \
        mainwindow.ui \
    sensorreadingswidget.ui \
    mechanicaltestingwidget.ui

INCLUDEPATH += /home/kirk/Downloads/boost_1_64_0/

LIBS += -L/home/kirk/Downloads/boost_1_64_0/stage/lib/ -lboost_system
LIBS += -L/home/kirk/Downloads/boost_1_64_0/stage/lib/ -lboost_filesystem
LIBS += -L/home/kirk/Downloads/boost_1_64_0/stage/lib/ -lboost_thread


# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

target.path = /home/pi
INSTALLS += target
