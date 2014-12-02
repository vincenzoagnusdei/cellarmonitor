#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include <QDialog>
#include <temperaturealarmlistmodel.h>
#include "eventlogger.h"



namespace Ui {
class AlarmDialog;
}

class AlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmDialog(QWidget *parent = 0, EventLogger *evlog=NULL);
    ~AlarmDialog();


private:
    Ui::AlarmDialog *ui;
    TemperatureAlarmListModel *model;   // model for the TemperatureAlarmList
    EventLogger *mpEventLogger;         // pointer to the EventLogger object

public slots:


};

#endif // ALARMDIALOG_H
