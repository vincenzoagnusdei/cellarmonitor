#include <QStringList>
#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "thresholdsetupdialog.h"
#include "databackupdialog.h"
#include "dialogmonitorcontrol.h"



const QString MainWindow::THREAD_T1 = "T1";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete mAlarmDialog;
    delete mTempMPThread;
}

void MainWindow::on_actionSetup_triggered()
{   
    mThresholdDialog.setModal(true);    
    mThresholdDialog.setWindowTitle("Setup Threshold");   
    mThresholdDialog.exec();

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

void MainWindow::init()
{

   qRegisterMetaType<EventLogger::EVENT_TYPE_ENUM>("EventLogger::EVENT_TYPE_ENUM");
   mTempMPThread = new MeasuringPointThread(this, 0,40);
   mTempMPThread->setObjectName(THREAD_T1);
   mAlarmDialog = new AlarmDialog(this, mTempMPThread);

   connect(mTempMPThread,SIGNAL(minThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)), &mEventLogger,
           SLOT(onMinThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)));
   connect(mTempMPThread,SIGNAL(maxThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)), &mEventLogger,
                   SLOT(onMaxThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)));
   connect(mTempMPThread,SIGNAL(currentValue(float,QString,EventLogger::EVENT_TYPE_ENUM)), &mEventLogger,                   SLOT(onCurrentValue(float,QString,EventLogger::EVENT_TYPE_ENUM)));


   connect(&mThresholdDialog, SIGNAL(thresholdsChanged()), this, SLOT(onThresholdsChanged()));

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

    if ( mFH.readMonitorStatus(&monitorstatus) == 1)
    {
        if (mFH.readThresholds(&thresholds) == 1)
        {
            if (monitorstatus.at(DialogMonitorControl::humidity).compare(DialogMonitorControl::ENABLED) == 0)
            {
                 if (!mTempMPThread->isRunning())
                 {
                    mTempMPThread->setMinThreshold(thresholds.at(ThresholdSetupDialog::hummin).toFloat());
                    mTempMPThread->setMaxThreshold(thresholds.at(ThresholdSetupDialog::hummax).toFloat());
                    mTempMPThread->setEmitValueTime(thresholds.at(ThresholdSetupDialog::humtime).toInt());
                    mTempMPThread->Stop=false;
                    mTempMPThread->start();
                }
            }
            else
            {
                mTempMPThread->Stop=true;
            }
/*
            if (vals.at(luminosity).compare(ENABLED) == 0)
            {

            }

            if (vals.at(temperature).compare(ENABLED) == 0)
            {

            }
*/
         }

    }




}

