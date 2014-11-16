#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDate>
#include <QTime>
#include <QDebug>
#include "dialogmonitorcontrol.h"
#include "eventlogger.h"



const QString EventLogger::LOG_TEMPERATURE_TH_CROSSED_FILE_A = "logtempthXa.txt";
const QString EventLogger::LOG_TEMPERATURE_TH_CROSSED_FILE_B = "logtempthXb.txt";
const QString EventLogger::LOG_HUMIDITY_TH_CROSSED_FILE_A = "loghumhXa.txt";
const QString EventLogger::LOG_HUMIDITY_TH_CROSSED_FILE_B = "loghumhXb.txt";
const QString EventLogger::LOG_LUMINOSITY_TH_CROSSED_FILE_A = "loglumXa.txt";
const QString EventLogger::LOG_LUMINOSITY_TH_CROSSED_FILE_B = "loghumhXb.txt";
const QString EventLogger::LOG_TEMPERATURE_CURRENT_VALUE_FILE_A = "logcurrvaltempa.txt";
const QString EventLogger::LOG_TEMPERATURE_CURRENT_VALUE_FILE_B = "logcurrvaltempa.txt";
const QString EventLogger::LOG_HUMIDITY_CURRENT_VALUE_FILE_A = "logcurrvalhuma.txt";
const QString EventLogger::LOG_HUMIDITY_CURRENT_VALUE_FILE_B = "logcurrvalhumb.txt";
const QString EventLogger::LOG_LUMINOSITY_CURRENT_VALUE_FILE_A = "logcurrvalluma.txt";
const QString EventLogger::LOG_LUMINOSITY_CURRENT_VALUE_FILE_B = "logcurrvallumb.txt";

const int EventLogger::LOG_SIZE = 500;
const int EventLogger::LENGHT_LINE = 26;

EventLogger::EventLogger(QObject *parent) :
    QObject(parent)
{
  }


void EventLogger::onMinThresholdCrossed(float val , float th, QString sensor, EVENT_TYPE_ENUM ev)
{
        QString event = QString::number(val);
        event.append(" ");
        event.append(QString::number(th));
        event.append(" ");
        event.append(sensor);
        EventLogger::writeEvent(event, ev);

}

void EventLogger::onMaxThresholdCrossed(float val , float th, QString sensor, EVENT_TYPE_ENUM ev)
{

    QString event = QString::number(val);
    event.append(" ");
    event.append(QString::number(th));
    event.append(" ");
    event.append(sensor);
    EventLogger::writeEvent(event, ev);

}

void EventLogger::onCurrentValue(float val, QString sensor, EVENT_TYPE_ENUM ev)
{
    QString event = QString::number(val);
    event.append(" ");
    event.append(sensor);
    writeEvent(event, ev);

}


int EventLogger::writeEvent(QString val, EVENT_TYPE_ENUM ev)
{
    QString filename = this->getFileName(ev);

    QFile file(filename);
        if (!file.open(QFile::Append | QFile::Text))
        {
                qDebug() <<  "Error opening file " << filename;
                return -1;
        }


        QString event = val;
        event.append(" ");
        event.append(QDate::currentDate().toString("dd.MM.yyyy"));
        event.append(" ");
        event.append(QTime::currentTime().toString("HH:mm"));
        event.append("\n");

        QTextStream datastream(&file);
        datastream << event;
        file.flush();
        file.close();

    return 1;

}


/*
 * Strategy for the log files
 * file A does not exist, return filename A
 * file A exist and size is < LOG_SIZE, return filname A
 * file A exist and size is > LOG_SIZE, file B does not exist, return filename B
 * file A exist and size is > LOG_SIZE, file B exist and size is < LOG_SIZE, return filename B
 * file A exist and size is > LOG_SIZE, file B exist and size is > LOG_SIZE, file A datetime < file B datetime, trunk and ret A
 * file A exist and sizr is > LOG_SIZE, file B exist and size is > LOG_SIZE, file A datetime > file B datetime, trunk and ret B
 */

QString EventLogger::getFileName(EVENT_TYPE_ENUM evtype)
{

    QFileInfo qfinfoa;
    QFileInfo qfinfob;
    QString filenamea;
    QString filenameb;
    QString filename = NULL;    

    switch(evtype)
    {
        case TEMPERATURE_TH:

            qfinfoa = QFileInfo(LOG_TEMPERATURE_TH_CROSSED_FILE_A);
            qfinfob = QFileInfo(LOG_TEMPERATURE_TH_CROSSED_FILE_B);
            filenamea = LOG_TEMPERATURE_TH_CROSSED_FILE_A;
            filenameb = LOG_TEMPERATURE_TH_CROSSED_FILE_B;

         break;

        case TEMPERATURE_VAL:
            qfinfoa = QFileInfo(LOG_TEMPERATURE_CURRENT_VALUE_FILE_A);
            qfinfob = QFileInfo(LOG_TEMPERATURE_CURRENT_VALUE_FILE_B);
            filenamea = LOG_TEMPERATURE_CURRENT_VALUE_FILE_A;
            filenameb = LOG_TEMPERATURE_CURRENT_VALUE_FILE_B;

        break;

        case HUMIDITY_TH:

            qfinfoa = QFileInfo(LOG_HUMIDITY_TH_CROSSED_FILE_A);
            qfinfob = QFileInfo(LOG_HUMIDITY_TH_CROSSED_FILE_B);
            filenamea = LOG_HUMIDITY_TH_CROSSED_FILE_A;
            filenameb = LOG_HUMIDITY_TH_CROSSED_FILE_B;

        break;

        case HUMIDITY_VAL:

            qfinfoa = QFileInfo(LOG_HUMIDITY_CURRENT_VALUE_FILE_A);
            qfinfob = QFileInfo(LOG_HUMIDITY_CURRENT_VALUE_FILE_B);
            filenamea = LOG_HUMIDITY_CURRENT_VALUE_FILE_A;
            filenameb = LOG_HUMIDITY_CURRENT_VALUE_FILE_B;

        break;

        case LUMINOSITY_TH:

            qfinfoa = QFileInfo(LOG_LUMINOSITY_TH_CROSSED_FILE_A);
            qfinfob = QFileInfo(LOG_LUMINOSITY_TH_CROSSED_FILE_A);
            filenamea = LOG_LUMINOSITY_TH_CROSSED_FILE_A;
            filenameb = LOG_LUMINOSITY_TH_CROSSED_FILE_A;

        break;

        case LUMINOSITY_VAL:

            qfinfoa = QFileInfo(LOG_LUMINOSITY_CURRENT_VALUE_FILE_A);
            qfinfob = QFileInfo(LOG_LUMINOSITY_CURRENT_VALUE_FILE_B);
            filenamea = LOG_LUMINOSITY_CURRENT_VALUE_FILE_A;
            filenameb = LOG_LUMINOSITY_CURRENT_VALUE_FILE_B;

        break;

        default:

            qDebug() << "Unknown event type";



     }




    if (qfinfoa.exists())
    {
        if (qfinfoa.size() < LOG_SIZE)
        {

            filename=filenamea;
        }
        else
        {

            if (qfinfob.exists())
            {
                 if (qfinfob.size() < LOG_SIZE)
                 {
                     filename=filenameb;
                 }
                 else
                 {
                     if (qfinfoa.lastModified() > qfinfob.lastModified())
                     {
                         filename=filenameb;
                         trunkateFile(filenameb);
                     }
                     else
                     {
                         filename=filenamea;
                         trunkateFile(filenamea);
                     }

                 }
             }
             else
             {
                  filename=filenameb;
             }

            }
    }
    else
    {
      filename=filenamea;
    }


    return filename;

}


void EventLogger::trunkateFile(QString filename)
{


    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        qDebug() <<  "Error opening file " << filename;

    }
    else
    {
        file.close();
    }


}
