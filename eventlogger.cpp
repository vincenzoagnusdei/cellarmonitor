#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDate>
#include <QTime>
#include <QDebug>
#include "dialogmonitorcontrol.h"
#include "eventlogger.h"
#include <assert.h>


const QString EventLogger::LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_A = "logmintempthXa.txt";
const QString EventLogger::LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_B = "logmintempthXb.txt";
const QString EventLogger::LOG_MIN_HUMIDITY_TH_CROSSED_FILE_A = "logminhumhXa.txt";
const QString EventLogger::LOG_MIN_HUMIDITY_TH_CROSSED_FILE_B = "logminhumhXb.txt";
const QString EventLogger::LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_A = "logminlumXa.txt";
const QString EventLogger::LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_B = "logminhumhXb.txt";

const QString EventLogger::LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_A = "logmaxtempthXa.txt";
const QString EventLogger::LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_B = "logmaxtempthXb.txt";
const QString EventLogger::LOG_MAX_HUMIDITY_TH_CROSSED_FILE_A = "logmaxhumhXa.txt";
const QString EventLogger::LOG_MAX_HUMIDITY_TH_CROSSED_FILE_B = "logmaxhumhXb.txt";
const QString EventLogger::LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_A = "logmaxlumXa.txt";
const QString EventLogger::LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_B = "logmaxhumhXb.txt";

const QString EventLogger::LOG_TEMPERATURE_CURRENT_VALUE_FILE_A = "logcurrvaltempa.txt";
const QString EventLogger::LOG_TEMPERATURE_CURRENT_VALUE_FILE_B = "logcurrvaltempa.txt";
const QString EventLogger::LOG_HUMIDITY_CURRENT_VALUE_FILE_A = "logcurrvalhuma.txt";
const QString EventLogger::LOG_HUMIDITY_CURRENT_VALUE_FILE_B = "logcurrvalhumb.txt";
const QString EventLogger::LOG_LUMINOSITY_CURRENT_VALUE_FILE_A = "logcurrvalluma.txt";
const QString EventLogger::LOG_LUMINOSITY_CURRENT_VALUE_FILE_B = "logcurrvallumb.txt";

const int EventLogger::LOG_SIZE = 100000;
const int EventLogger::LENGHT_LINE = 26;

EventLogger::EventLogger(QObject *parent) :
    QObject(parent)
{
  }


void EventLogger::onMinThresholdCrossed(float val , float th, QString sensor, EVENT_TYPE_ENUM ev)
{

    QString event = this->prepareEventForFile(val , th, sensor, ev);
    this->writeEvent(event, ev);
    event=this->prepareAlarmEventForGUI(val , th, sensor, ev);
    tresholdCrossed(event);


}

void EventLogger::onMaxThresholdCrossed(float val , float th, QString sensor, EVENT_TYPE_ENUM ev)
{

    QString event = this->prepareEventForFile(val , th, sensor, ev);
    this->writeEvent(event, ev);
    event=this->prepareAlarmEventForGUI(val , th, sensor, ev);
    tresholdCrossed(event);

}

void EventLogger::onCurrentValue(float val, QString sensor, EVENT_TYPE_ENUM ev)
{

    QString event=this->prepareEventForFile(val, -1, sensor, ev);
    this->writeEvent(event, ev);

}


QString EventLogger::prepareAlarmEventForGUI(float val , float th, QString sensor, EVENT_TYPE_ENUM ev)
{
    QString event;

    event= QDate::currentDate().toString("dd.MM.yyyy");
    event.append(" ");
    event.append(QTime::currentTime().toString("HH:mm"));    
    event.append("              ");
    if (QString::number(val).size() == 1)
    {
         event.append("  ");
    }
    event.append(QString::number(val));    
    event.append("                 ");

    if (QString::number(th).size() == 1)
    {
         event.append("  ");
    }
    event.append(QString::number(th));    
    event.append("               ");

    event.append(sensor);

    return event;


}

QString EventLogger::prepareEventForFile(float val , float th, QString sensor, EVENT_TYPE_ENUM ev)
{     

    QString event;

    event= QDate::currentDate().toString("dd.MM.yyyy");
    event.append(" ");
    event.append(QTime::currentTime().toString("HH:mm"));
    event.append(",");
    event.append(QString::number(val));
    event.append(",");

    if (th != -1.0)
    {   // add value becuase is a threshold crossing
        event.append(QString::number(th));
        event.append(",");
    }

    event.append(sensor);
    event.append(",");
    event.append("\n");

    return event;


}

int EventLogger::writeEvent(QString event, EVENT_TYPE_ENUM ev)
{

    QString filename = this->getFileLogName(ev);

    assert (filename!=NULL);

    QFile file(filename);
    if (!file.open(QFile::Append | QFile::Text))
    {
            qDebug() <<  "Error opening file " << filename;
            return -1;
    }


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

QString EventLogger::getFileLogName(EVENT_TYPE_ENUM evtype)
{

    QFileInfo qfinfoa;
    QFileInfo qfinfob;   
    QString filenamea;
    QString filenameb;
    QString filename;

    filename.clear();


    this->getFileNames(evtype, &filenamea, &filenameb);

    assert(filenamea.size() > 0 && filenameb.size());

    qfinfoa.setFile(filenamea);
    qfinfob.setFile(filenameb);


    if (qfinfoa.exists())
    {
        if (qfinfoa.size() < LOG_SIZE)
        {

            filename=qfinfoa.fileName();
        }
        else
        {

            if (qfinfob.exists())
            {
                 if (qfinfob.size() < LOG_SIZE)
                 {
                     filename=qfinfob.fileName();
                 }
                 else
                 {
                     if (qfinfoa.lastModified() > qfinfob.lastModified())
                     {
                         filename=qfinfob.fileName();
                         trunkateFile(filename);
                     }
                     else
                     {
                         filename=qfinfoa.fileName();
                         trunkateFile(filename);
                     }

                 }
             }
             else
             {
                  filename=qfinfob.fileName();
             }

            }
    }
    else
    {
      filename=qfinfoa.fileName();
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


void EventLogger::getFileNames(EVENT_TYPE_ENUM evtype, QString *filenamea, QString  *filenameb)
{

    filenamea->clear();
    filenameb->clear();

    switch(evtype)
    {
        case TEMPERATURE_MIN_TH:

            filenamea->append(LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_A);
            filenameb->append(LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_B);

         break;

        case TEMPERATURE_MAX_TH:

            filenamea->append(LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_A);
            filenameb->append(LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_B);

         break;

        case TEMPERATURE_VAL:
            filenamea->append(LOG_TEMPERATURE_CURRENT_VALUE_FILE_A);
            filenameb->append(LOG_TEMPERATURE_CURRENT_VALUE_FILE_B);

        break;

        case HUMIDITY_MIN_TH:

            filenamea->append(LOG_MIN_HUMIDITY_TH_CROSSED_FILE_A);
            filenameb->append(LOG_MIN_HUMIDITY_TH_CROSSED_FILE_B);

        break;

        case HUMIDITY_MAX_TH:

            filenamea->append(LOG_MAX_HUMIDITY_TH_CROSSED_FILE_A);
            filenameb->append(LOG_MAX_HUMIDITY_TH_CROSSED_FILE_B);

        break;


        case HUMIDITY_VAL:

            filenamea->append(LOG_HUMIDITY_CURRENT_VALUE_FILE_A);
            filenameb->append(LOG_HUMIDITY_CURRENT_VALUE_FILE_B);

        break;

        case LUMINOSITY_MIN_TH:

            filenamea->append(LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_A);
            filenameb->append(LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_A);

        break;

        case LUMINOSITY_MAX_TH:

            filenamea->append(LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_A);
            filenameb->append(LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_A);

        break;

        case LUMINOSITY_VAL:

            filenamea->append(LOG_LUMINOSITY_CURRENT_VALUE_FILE_A);
            filenameb->append(LOG_LUMINOSITY_CURRENT_VALUE_FILE_B);

        break;

        default:

            qDebug() << "Unknown event type";



     }

}

int EventLogger::readAllEventThresholds(QStringList *vals, EVENT_TYPE_ENUM evtype)
{
    QFileInfo qfinfoa;
    QFileInfo qfinfob;
    QString filenamea;
    QString filenameb;
    QString filename;
    QString data;

    filename.clear();
    filenamea.clear();
    filenameb.clear();

    this->getFileNames(evtype, &filenamea, &filenameb);

    qfinfoa.setFile(filenamea);
    qfinfob.setFile(filenameb);


    if (qfinfoa.exists() == true)
    {
        if (qfinfob.exists() == true)
        {

            if (qfinfoa.lastModified() > qfinfob.lastModified())
            {
                filename = qfinfoa.fileName();

            }
            else
            {

                filename = qfinfob.fileName();
            }

        }
        else
        {
            filename = qfinfoa.fileName();
        }
    }
    else
    {
        if (qfinfob.exists() == true)
        {

            filename = qfinfob.fileName();

        }

    }



    QFile file(filename);
      if (!file.open(QFile::ReadOnly ))
          return -1;

    QTextStream in(&file);

    while (!in.atEnd()) {
        data = in.readAll();

    }

    *vals = data.split(',');

    file.close();

    return 1;

}

/*
 * Get date of the last file update as QStringList
 *
 */

QStringList EventLogger::getFileInfoUpdate()
{
    QStringList fileupdateinfo;
    QString s;

    QString fn = this->getFileLogName(TEMPERATURE_MIN_TH);

    assert (fn!=NULL);

    QFileInfo qfinfo = QFileInfo(fn);

    QDateTime lastmodifiedth(qfinfo.lastModified());

    fileupdateinfo.append(qfinfo.fileName());
    fileupdateinfo.append(" ");
    fileupdateinfo.append(QString::number(lastmodifiedth.toMSecsSinceEpoch()));
    fileupdateinfo.append(" ");


    fn = this->getFileLogName(TEMPERATURE_VAL);

    assert (fn!=NULL);

    qfinfo.setFile(qfinfo.fileName());

    QDateTime lastmodified(qfinfo.lastModified());

    fileupdateinfo.append(fn);
    fileupdateinfo.append(" ");
    fileupdateinfo.append(QString::number(lastmodified.toMSecsSinceEpoch()));
    fileupdateinfo.append("\n");

    return fileupdateinfo;
}



