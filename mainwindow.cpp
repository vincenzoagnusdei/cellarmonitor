#include <QStringList>
#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "thresholdsetupdialog.h"
#include "databackupdialog.h"
#include "dialogmonitorcontrol.h"
#include <QThread>
#include <QDir>



const QString MainWindow::THREAD_T1 = "T1";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDir::setCurrent(FileHandler::FILE_DIRECTORY);

    ui->setupUi(this);    

    mpCoapServerThread = new COAPServer(this);    
    mpTempMPThread = new MeasuringPointThread(this, 0,40);
    mpTempMPThread->setObjectName(THREAD_T1);    
    mAlarmDialog = new AlarmDialog(this, &mEventLogger);
    mpHttpDaemon = new HttpDaemon(this);   

    qRegisterMetaType<EventLogger::EVENT_TYPE_ENUM>("EventLogger::EVENT_TYPE_ENUM");
    connect(mpTempMPThread,SIGNAL(minThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)), &mEventLogger,
            SLOT(onMinThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)));
    connect(mpTempMPThread,SIGNAL(maxThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)), &mEventLogger,
                    SLOT(onMaxThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)));
    connect(mpTempMPThread,SIGNAL(currentValue(float,QString,EventLogger::EVENT_TYPE_ENUM)), &mEventLogger,
            SLOT(onCurrentValue(float,QString,EventLogger::EVENT_TYPE_ENUM)));
    connect(&mThresholdSetupDialog, SIGNAL(thresholdsChanged()), this, SLOT(onThresholdsChanged()));


    this->startThreads();

    qDebug() <<  "----------------------------------Main" << QThread::currentThreadId();

}

MainWindow::~MainWindow()
{
    delete ui;
    if (mAlarmDialog != NULL)
        delete mAlarmDialog;
    delete mpTempMPThread;
    delete mpCoapServerThread;
    delete mpHttpDaemon;   
}

void MainWindow::on_actionSetup_triggered()
{   
    mThresholdSetupDialog.setModal(true);
    mThresholdSetupDialog.setWindowTitle("Setup Threshold");
    mThresholdSetupDialog.exec();

}

void MainWindow::on_actionBackup_triggered()
{
    DataBackupDialog dataBackupDialog;
    dataBackupDialog.setModal(true);
    dataBackupDialog.setWindowTitle("Data Backup");
    dataBackupDialog.exec();
}

void MainWindow::on_actionStatus_triggered()
{
    DialogMonitorControl mDialogMonitorStatus;
    mDialogMonitorStatus.setModal(true);
    mDialogMonitorStatus.setWindowTitle("Monitor Status");
    connect(&mDialogMonitorStatus,SIGNAL(monitorControlChanged()), this, SLOT(onStartMonitoringChanged()));
    mDialogMonitorStatus.exec();

}


void MainWindow::on_actionDisplay_triggered()
{
    mAlarmDialog->setModal(true);
    mAlarmDialog->setWindowTitle("Crossed Thresholds Alarm");
    mAlarmDialog->exec();

}



void MainWindow::onStartMonitoringChanged()
{

    this->startThreads();
}




void MainWindow::onThresholdsChanged()
{
    startThreads();
}

void MainWindow::startThreads()
{
    QStringList monitorstatus;
    QStringList thresholds;


    if (!mpCoapServerThread->isRunning())
    {
        mpCoapServerThread->start();
    }


    if ( mFH.readMonitorStatus(&monitorstatus) == 1)
    {
        if (mFH.readThresholds(&thresholds) == 1)
        {
            if (monitorstatus.at(DialogMonitorControl::temperature).compare(DialogMonitorControl::ENABLED) == 0)
            {
                 if (!mpTempMPThread->isRunning())
                 {
                    mpTempMPThread->setMinThreshold(thresholds.at(ThresholdSetupDialog::tempmin).toFloat());
                    mpTempMPThread->setMaxThreshold(thresholds.at(ThresholdSetupDialog::tempmax).toFloat());
                    mpTempMPThread->setEmitValueTime(thresholds.at(ThresholdSetupDialog::temptime).toInt());
                    mpTempMPThread->Stop=false;
                    mpTempMPThread->start();
                }
            }
            else
            {
                mpTempMPThread->Stop=true;
            }
/*
            if (vals.at(luminosity).compare(ENABLED) == 0)
            {

            }

            if (vals.at(humidity).compare(ENABLED) == 0)
            {

            }
*/
         }

    }




}


FileHandler* MainWindow::getFileHanlder()
{
    return &mFH;
}

EventLogger* MainWindow::getEventLoggerHanlder()
{
    return &mEventLogger;
}




MeasuringPointThread* MainWindow::getTemperatureThreadInstance()
{
    return mpTempMPThread;
}

void MainWindow::on_actionThTemperature_triggered(){

    mThresholdLogDialog.setModal(true);
    mThresholdLogDialog.setWindowTitle("Event Threshold Log");
    mThresholdLogDialog.exec();

}

void MainWindow::on_actionParameters_triggered()
{
    mParametersDialog.exec();
}
