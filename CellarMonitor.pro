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
    filehandler.cpp

HEADERS  += mainwindow.h \
    databackupdialog.h \
    filehandler.h \
    thresholdsetupdialog.h

FORMS    += mainwindow.ui \
    databackupdialog.ui \
    thresholdsetupdialog.ui
