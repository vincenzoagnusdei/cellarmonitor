#ifndef TEMPERATUREALARMLISTMODEL_H
#define TEMPERATUREALARMLISTMODEL_H

#include <QStringListModel>
#include <QStringList>
#include <eventlogger.h>


class TemperatureAlarmListModel : public QStringListModel
{
    Q_OBJECT
public:
    explicit TemperatureAlarmListModel(QObject *parent = 0);

signals:

public slots:
    void onMinThresholdCrossed(float, float, QString, EventLogger::EVENT_TYPE_ENUM );
    void onMaxThresholdCrossed(float, float, QString, EventLogger::EVENT_TYPE_ENUM );
    void onCurrentValue(float, QString , EventLogger::EVENT_TYPE_ENUM );

private:
    QStringList mAlarmList;


};

#endif // TEMPERATUREALARMLISTMODEL_H
