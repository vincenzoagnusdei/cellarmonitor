#include "filehandler.h"
#include <iostream>
using namespace std;
#include <QDebug>
#include <QStringList>


const QString FileHandler::THRESHOLDS_FILE = "thresholds.txt";

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

    return 1;

}


