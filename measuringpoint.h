#ifndef MEASURINGPOINT_H
#define MEASURINGPOINT_H

#include <QThread>

class MeasuringPoint : public QThread
{
    Q_OBJECT
public:
    explicit MeasuringPoint(QObject *parent = 0);

signals:

public slots:

};

#endif // MEASURINGPOINT_H
