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

    void onTresholdCrossed(QString);
    /* void currentValue(QString); */


private:
    QStringList mAlarmList;


};

#endif // TEMPERATUREALARMLISTMODEL_H
