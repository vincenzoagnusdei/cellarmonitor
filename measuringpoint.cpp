#include "measuringpoint.h"
#include <QtCore>


MeasuringPointThread::MeasuringPointThread(QObject *parent, int low, int high) :
    QThread(parent)
{
    this->mHigh=high;
    this->mLow=low;    
    this->mMinTh=0;
    this->mMaxTh=0;
    this->mEmitTime=0;

}


void MeasuringPointThread::run()
{
    QMutex mutex;
    int minutes=2;

    do
    {

        mutex.lock();
        if (this->Stop)
        {
            break;
        }

        mutex.unlock();

        this->msleep(60000);
        minutes++;
        int curval =  getRandomValue();
        if ((this->mEmitTime % minutes == 0) && (minutes >= this->mEmitTime) )
        {

            emit currentValue(curval, this->objectName(), EventLogger::TEMPERATURE_VAL);
        }

        if (curval < mMinTh)
            emit minThresholdCrossed(curval, this->mMinTh, this->objectName(), EventLogger::TEMPERATURE_MIN_TH);
        if (curval>  mMaxTh)
            emit maxThresholdCrossed(curval, this->mMaxTh, this->objectName(), EventLogger::TEMPERATURE_MAX_TH);


    } while(!Stop);

    minutes=2;

}



void MeasuringPointThread::setEmitValueTime(int seconds)
{
    this->mEmitTime=seconds;
}

void MeasuringPointThread::setMinThreshold(float minth)
{
    this->mMinTh=minth;
}

void MeasuringPointThread::setMaxThreshold(float maxth)
{
    this->mMaxTh=maxth;
}

int MeasuringPointThread::getRandomValue()
{

 return qrand() % ((mHigh + 1) - mLow) + mLow;
}

 int MeasuringPointThread::getValue()
 {
     return this->getRandomValue();
 }
