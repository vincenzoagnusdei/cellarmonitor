#include "temperaturealarmlistmodel.h"
#include "eventlogger.h"

TemperatureAlarmListModel::TemperatureAlarmListModel(QObject *parent) :
    QStringListModel(parent)
{
   this->setStringList(this->mAlarmList);
}



void TemperatureAlarmListModel::onTresholdCrossed(QString event)
{
    mAlarmList.append(event);
    this->setStringList(mAlarmList);
}

/*
void TemperatureAlarmListModel::onCurrentValue(QString event)
{
    mAlarmList.append(event);
    this->setStringList(mAlarmList);
}
*/

