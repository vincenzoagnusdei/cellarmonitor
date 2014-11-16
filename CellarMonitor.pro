#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T12:52:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CellarMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databackupdialog.cpp \
    thresholdsetupdialog.cpp \
    filehandler.cpp \
    dialogmonitorcontrol.cpp \
    measuringpoint.cpp \
    eventlogger.cpp \
    alarmdialog.cpp \
    temperaturealarmlistmodel.cpp

HEADERS  += mainwindow.h \
    databackupdialog.h \
    filehandler.h \
    thresholdsetupdialog.h \
    dialogmonitorcontrol.h \
    measuringpoint.h \
    eventlogger.h \
    alarmdialog.h \
    temperaturealarmlistmodel.h

FORMS    += mainwindow.ui \
    databackupdialog.ui \
    thresholdsetupdialog.ui \
    dialogmonitorcontrol.ui \
    alarmdialog.ui
