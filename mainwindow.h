#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "measuringpoint.h"
#include "filehandler.h"
#include "thresholdsetupdialog.h"
#include "eventlogger.h"
#include "alarmdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    static const QString THREAD_T1;


private slots:
    void on_actionSetup_triggered();
    void on_actionBackup_triggered();
    void on_actionStatus_triggered();

    void on_actionDisplay_triggered();

private:
    Ui::MainWindow *ui;
    MeasuringPointThread *mTempMPThread=NULL;
    MeasuringPointThread *mLumMPThread=NULL;
    MeasuringPointThread *mHumMPThread=NULL;
    ThresholdSetupDialog mThresholdDialog;
    AlarmDialog *mAlarmDialog;

    EventLogger mEventLogger;
    FileHandler mFH;
    void startThreads();


    void startMonitoring();

public slots:
    void onStartMonitoringChanged();
    void onThresholdsChanged();


};

#endif // MAINWINDOW_H
