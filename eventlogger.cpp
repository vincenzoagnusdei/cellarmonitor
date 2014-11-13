#include <QFile>
#include <QString>
#include <QDate>
#include <QTime>
#include <QDebug>

#include "eventlogger.h"



const QString EventLogger::LOG_FILE = "logfile.txt";
const int EventLogger::LENGHT_LINE = 26;

EventLogger::EventLogger(QObject *parent) :
    QObject(parent)
{
}


void EventLogger::onMinThresholdCrossed(float val , float th, QString sensor)
{
        QString event = QString::number(val);
        event.append(" ");
        event.append(QString::number(th));
        event.append(" ");
        event.append(sensor);
        EventLogger::writeEvent(event);

}

void EventLogger::onMaxThresholdCrossed(float val , float th, QString sensor)
{

    QString event = QString::number(val);
    event.append(" ");
    event.append(QString::number(th));
    event.append(" ");
    event.append(sensor);
    EventLogger::writeEvent(event);

}

void EventLogger::onCurrentValue(float val, QString sensor)
{
    QString event = QString::number(val);
    event.append(" ");
    event.append(sensor);
    writeEvent(event);

}


int EventLogger::writeEvent(QString val)
{

    QFile file(EventLogger::LOG_FILE);
        if (!file.open(QFile::Append | QFile::Text))
        {
                qDebug() <<  "Error opening file " << LOG_FILE;
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
