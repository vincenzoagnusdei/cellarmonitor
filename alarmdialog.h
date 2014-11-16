#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include <QDialog>
#include <temperaturealarmlistmodel.h>
#include "measuringpoint.h"



namespace Ui {
class AlarmDialog;
}

class AlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmDialog(QWidget *parent = 0, MeasuringPointThread *mp=NULL);

    ~AlarmDialog();


private:
    Ui::AlarmDialog *ui;
    TemperatureAlarmListModel *model;
    MeasuringPointThread *mMPT;

public slots:
    void updateAlarmList()
    {

    }

};

#endif // ALARMDIALOG_H
