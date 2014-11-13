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
    int seconds=0;

    do
    {

        mutex.lock();
        if (this->Stop)
        {
            break;
        }

        mutex.unlock();

        this->msleep(1000);
        seconds++;
        if (seconds != 1 && (this->mEmitTime % seconds == 0) && (this->mEmitTime < seconds) )
        {
            int curval = getRandomValue();
            emit currentValue(curval, this->objectName());
            if (curval < mMinTh)
                emit minThresholdCrossed(curval, this->mMinTh, this->objectName());
            if (curval>  mMaxTh)
                emit maxThresholdCrossed(curval, this->mMaxTh, this->objectName());
        }
        else
        {
            int curval = getRandomValue();

            if (curval < mMinTh)
                emit minThresholdCrossed(curval, this->mMinTh, this->objectName());
            if (curval>  mMaxTh)
                emit maxThresholdCrossed(curval, this->mMaxTh, this->objectName());

        }

    } while(!Stop);

    seconds=0;

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
