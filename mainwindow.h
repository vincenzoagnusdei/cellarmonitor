#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "coapserver.h"
#include "measuringpoint.h"
#include "filehandler.h"
#include "thresholdsetupdialog.h"
#include "eventlogger.h"
#include "alarmdialog.h"
#include "thresholdlogdialog.h"
#include "httpdaemon.h"
#include "parametersdialog.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();   
    static const QString THREAD_T1;
    MeasuringPointThread* getTemperatureThreadInstance();
    FileHandler* getFileHanlder();       
    EventLogger* getEventLoggerHanlder();


private slots:
    void on_actionSetup_triggered();
    void on_actionBackup_triggered();
    void on_actionStatus_triggered();
    void on_actionDisplay_triggered();
    void on_actionThTemperature_triggered();

    void on_actionParameters_triggered();

private:
    Ui::MainWindow *ui;
    MeasuringPointThread *mpTempMPThread=NULL;
    MeasuringPointThread *mpLumMPThread=NULL;
    MeasuringPointThread *mpHumMPThread=NULL;
    COAPServer *mpCoapServerThread=NULL;   
    ThresholdSetupDialog mThresholdSetupDialog;    
    ParametersDialog mParametersDialog;
    AlarmDialog *mAlarmDialog=NULL;
    HttpDaemon *mpHttpDaemon;
    EventLogger mEventLogger;
    FileHandler mFH;
    ThresholdLogDialog mThresholdLogDialog;
    void startThreads();
    void startMonitoring();

public slots:
    void onStartMonitoringChanged();
    void onThresholdsChanged();


};

#endif // MAINWINDOW_H
