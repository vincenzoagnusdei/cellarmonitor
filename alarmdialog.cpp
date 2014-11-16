#include "alarmdialog.h"
#include "ui_alarmdialog.h"



AlarmDialog::AlarmDialog(QWidget *parent, MeasuringPointThread *mp) :
    QDialog(parent),
    ui(new Ui::AlarmDialog)
{
    mMPT = mp;
    ui->setupUi(this);
    model = new TemperatureAlarmListModel(this);
    ui->alarmlistView->setModel(model);

    connect(mp, SIGNAL(minThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)), model,
            SLOT(onMinThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)));
    connect(mp, SIGNAL(maxThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)), model,
            SLOT(onMaxThresholdCrossed(float,float,QString,EventLogger::EVENT_TYPE_ENUM)));

}

AlarmDialog::~AlarmDialog()
{
    delete ui;
}
