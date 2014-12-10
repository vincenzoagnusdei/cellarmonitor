#include "filehandler.h"
#include <iostream>
#include <QDebug>
#include <QStringList>
#include <QFileInfo>

using namespace std;

const QString FileHandler::THRESHOLDS_FILE = "thresholds.txt";
const QString FileHandler::MONITOR_STATUS_FILE = "monitorstatus.txt";
const QString FileHandler::PARAMETER_FILE = "parameters.txt";
const QString FileHandler::FILE_DIRECTORY="/home/cellarmonitor/";


FileHandler::FileHandler()
{
    INIT_MONITOR_STATUS_FILE = "0,0,0"; /* data init to monitor disable check of thresholds */
    INIT_THRESHOLDS_FILE = "12,21,63,11,22,64,10,25,63"; /* data to init the thresholds file hum, lum. temp */

    // this->initParameters();
}

FileHandler::~FileHandler()
{

}



int FileHandler::writeThresholds(QString *data)
{


    QFile file(THRESHOLDS_FILE);
        if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
            return -1;

        QTextStream datastream(&file);

        datastream << *data;

         file.close();

     return 1;

}


int FileHandler::readThresholds(QStringList *vals)
{
    QString thresholds;
    QFileInfo fileinfo= QFileInfo(THRESHOLDS_FILE);

    if (!fileinfo.exists())
    {
        if (this->writeThresholds(&INIT_THRESHOLDS_FILE) == -1)
        {
            qDebug() << "Error initializing thresholds file";
            return -1;
        }

    }

    QFile file(THRESHOLDS_FILE);
    if (!file.open(QFile::ReadOnly ))
    {

        qDebug() << "Error opening thresholds file";
        return -1;

    }


    QTextStream in(&file);
    while (!in.atEnd()) {
      thresholds = in.readAll();

    }

    *vals = thresholds.split(',');

    file.close();

    return 1;

}

int FileHandler::writeMonitorStatus(QString *vals)
{


    QFile file(MONITOR_STATUS_FILE);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        qDebug() << "Error writing file " << MONITOR_STATUS_FILE;
        return -1;
    }


    QTextStream datastream(&file);
    datastream << *vals;
    file.flush();
    file.close();

     return 1;

}


int FileHandler::readMonitorStatus(QStringList *vals)
{
    QString monitorstatus;
    QFileInfo fileinfo = QFileInfo(MONITOR_STATUS_FILE);

    if (!fileinfo.exists())
    {
        if (this->writeMonitorStatus(&INIT_MONITOR_STATUS_FILE) == -1)
        {
            qDebug() << "Error initializing Monitor Status file";
            return -1;
        }

    }


    QFile file(MONITOR_STATUS_FILE);
    if (!file.open(QFile::ReadOnly ))
    {
        qDebug() << "Error opening Monitor Status File";
    }


    QTextStream in(&file);
    while (!in.atEnd()) {
      monitorstatus = in.readAll();

    }

    *vals = monitorstatus.split(',');
    file.close();

    return 1;

}



int FileHandler::readParameters(QStringList *vals)
{
    QString parameters;
    QFileInfo fileinfo = QFileInfo(PARAMETER_FILE);

    if (!fileinfo.exists())
    {
        this->initParameters(&parameters);
        if (this->writeParameters(&parameters) == -1)
        {
            qDebug() << "Error initializing parameter file";
            return -1;
        }

    }


    QFile file(PARAMETER_FILE);
    if (!file.open(QFile::ReadOnly ))
    {
        qDebug() << "Error opening Parameter File";
        return -1;
    }


    QTextStream in(&file);
    while (!in.atEnd()) {
      parameters = in.readAll();

    }

    *vals = parameters.split('\n');
    file.close();

    return 1;

}

void FileHandler::initParameters(QString *val)
{
    QString ip=NULL;

    val->append(PORTNUM);


}

int FileHandler::writeParameters(QString *vals)
{


    QFile file(PARAMETER_FILE);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        qDebug() << "Error writing file " << PARAMETER_FILE;
        return -1;
    }

    QTextStream datastream(&file);
    datastream << *vals;
    file.flush();
    file.close();

     return 1;

}


