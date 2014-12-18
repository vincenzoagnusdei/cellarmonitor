#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T12:52:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CellarMonitor
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c99

unix:!macx: LIBS += -lcantcoap

target.path = /root/opt/myapp
INSTALLS += target

SOURCES += main.cpp\
        mainwindow.cpp \
    databackupdialog.cpp \
    thresholdsetupdialog.cpp \
    filehandler.cpp \
    dialogmonitorcontrol.cpp \
    measuringpoint.cpp \
    eventlogger.cpp \
    alarmdialog.cpp \
    temperaturealarmlistmodel.cpp \
    thresholdlogdialog.cpp \
    coapserver.cpp \
    nethelper.c \
    httpdaemon.cpp \
    parametersdialog.cpp

HEADERS  += mainwindow.h \
    databackupdialog.h \
    filehandler.h \
    thresholdsetupdialog.h \
    dialogmonitorcontrol.h \
    measuringpoint.h \
    eventlogger.h \
    alarmdialog.h \
    temperaturealarmlistmodel.h \
    thresholdlogdialog.h \
    coapserver.h \
    httpdaemon.h \
    parametersdialog.h

FORMS    += mainwindow.ui \
    databackupdialog.ui \
    thresholdsetupdialog.ui \
    dialogmonitorcontrol.ui \
    alarmdialog.ui \
    thresholdlogdialog.ui \
    parametersdialog.ui
