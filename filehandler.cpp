#include "filehandler.h"
#include <iostream>
#include <QDebug>
#include <QStringList>

using namespace std;

const QString FileHandler::THRESHOLDS_FILE = "thresholds.txt";
const QString FileHandler::MONITOR_STATUS_FILE = "monitorstatus.txt";

FileHandler::FileHandler()
{

}

FileHandler::~FileHandler()
{

}



int FileHandler::writeThresholds(QString *data)
{


    QFile file(FileHandler::THRESHOLDS_FILE);
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

    QFile file(FileHandler::THRESHOLDS_FILE);
      if (!file.open(QFile::ReadOnly ))
          return -1;

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


    QFile file(FileHandler::MONITOR_STATUS_FILE);        
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        qDebug() << "Error writing file " << FileHandler::MONITOR_STATUS_FILE;
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

    QFile file(FileHandler::MONITOR_STATUS_FILE);
      if (!file.open(QFile::ReadOnly ))
          return -1;

      QTextStream in(&file);
      while (!in.atEnd()) {
          monitorstatus = in.readAll();

      }

      *vals = monitorstatus.split(',');
      file.close();

    return 1;

}


