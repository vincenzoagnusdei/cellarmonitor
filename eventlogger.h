#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <QObject>

class EventLogger : public QObject
{
    Q_OBJECT
public:
    static const QString LOG_FILE;
    static const int LENGHT_LINE;
    explicit EventLogger(QObject *parent = 0);
    int writeEvent(QString);

signals:

public slots:

    void onMinThresholdCrossed(float, float, QString);
    void onMaxThresholdCrossed(float, float, QString);
    void onCurrentValue(float, QString);


};

#endif // EVENTLOGGER_H
