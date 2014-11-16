#include "temperaturealarmlistmodel.h"
#include "eventlogger.h"

TemperatureAlarmListModel::TemperatureAlarmListModel(QObject *parent) :
    QStringListModel(parent)
{
   this->mAlarmList.append("aaaaaaaa");
    this->mAlarmList.append("aaaaaaaa");
    this->mAlarmList.append("aaaaaaaa");
    this->mAlarmList.append("aaaaaaaa");
   this->setStringList(this->mAlarmList);


}



void TemperatureAlarmListModel::onMinThresholdCrossed(float val , float th, QString sensor, EventLogger::EVENT_TYPE_ENUM ev)
{

    QString event = QString::number(val);
    event.append(" ");
    event.append(QString::number(th));
    event.append(" ");
    event.append(sensor);
    mAlarmList.append(event);

     this->setStringList(mAlarmList);



}

void TemperatureAlarmListModel::onMaxThresholdCrossed(float val , float th, QString sensor, EventLogger::EVENT_TYPE_ENUM ev)
{

    QString event = QString::number(val);
    event.append(" ");
    event.append(QString::number(th));
    event.append(" ");
    event.append(sensor);
    // mAlarmList.append(event);


}

void TemperatureAlarmListModel::onCurrentValue(float val, QString sensor, EventLogger::EVENT_TYPE_ENUM ev)
{
    QString event = QString::number(val);
    event.append(" ");
    event.append(sensor);


}
