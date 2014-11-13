#include "dialogmonitorcontrol.h"
#include "ui_dialogmonitorcontrol.h"
#include <QDebug>


#include <QSystemInfo>



const QString DialogMonitorControl::ENABLED = "1";
const QString DialogMonitorControl::DISABLED = "0";


DialogMonitorControl::DialogMonitorControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMonitorControl)
{
    ui->setupUi(this);
    initMonitorStatus();
}

DialogMonitorControl::~DialogMonitorControl()
{
    delete ui;
}


int DialogMonitorControl::initMonitorStatus()
{
    QStringList vals;

    if ( mFH.readMonitorStatus(&vals) != 1)
    {
        qDebug() << "Error reading Monitor Status";
        return -1;
    }
    else
    {

        if (vals.at(humidity).compare(ENABLED) == 0)
        {
         ui->cbStartHumidity->setChecked(true);
        }
        else
        {
          ui->cbStartHumidity->setChecked(false);
        }
        if (vals.at(luminosity).compare(ENABLED) == 0)
        {
         ui->cbStartLuminosity->setChecked(true);
        }
        else
        {
          ui->cbStartLuminosity->setChecked(false);
        }
        if (vals.at(temperature).compare(ENABLED) == 0)
        {
         ui->cbStartTemperature->setChecked(true);
        }
        else
        {
          ui->cbStartTemperature->setChecked(false);
        }

    }

    return 1;
}

void DialogMonitorControl::on_buttonBox_accepted()
{

         QString str;

         if (ui->cbStartHumidity->isChecked())
        {
         str.append(ENABLED);
        }
         else
        {
         str.append(DISABLED);
        }

         str.append(",");

         if (ui->cbStartLuminosity->isChecked())
        {
         str.append(ENABLED);
        }
         else
        {
         str.append(DISABLED);
        }
         str.append(",");

         if (ui->cbStartTemperature->isChecked())
        {
         str.append(ENABLED);
        }
         else
        {
         str.append(DISABLED);
        }        

         if ( mFH.writeMonitorStatus(&str) != 1)
         {
             qDebug() << "Error writing Monitor Status";
         }

        emit monitorControlChanged();
}

void DialogMonitorControl::checkDiskSpaceForLogEvent()
{

    QtMobility::QSystemStorageInfo sysStrgInfo;
    QStringList drives = sysStrgInfo.logicalDrives();

    foreach (QString drive, drives)
    {
        qDebug() << sysStrgInfo.availableDiskSpace(drive);
        qDebug() << sysStrgInfo.totalDiskSpace(drive);
    }





}
