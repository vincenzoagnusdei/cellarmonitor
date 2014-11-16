#ifndef MEASURINGPOINT_H
#define MEASURINGPOINT_H

#include <QThread>
#include <QString>
#include "eventlogger.h"

class MeasuringPointThread : public QThread
{
    Q_OBJECT
public:
    explicit MeasuringPointThread(QObject *parent = 0, int low=0, int high=0);
    void setEmitValueTime(int seconds);
    void setMinThreshold(float minth);
    void setMaxThreshold(float maxth);
    bool Stop;

protected:
    void run();

signals:
    void minThresholdCrossed(float, float, QString, EventLogger::EVENT_TYPE_ENUM);
    void maxThresholdCrossed(float, float, QString, EventLogger::EVENT_TYPE_ENUM);
    void currentValue(float, QString, EventLogger::EVENT_TYPE_ENUM);

public slots:

private:
    float mMinTh;
    float mMaxTh;
    int mEmitTime;
    int mHigh;
    int mLow;
    int getRandomValue();

};

#endif // MEASURINGPOINT_H
