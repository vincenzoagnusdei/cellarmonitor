#include "alarmdialog.h"
#include "ui_alarmdialog.h"



AlarmDialog::AlarmDialog(QWidget *parent, EventLogger *evlog) :
    QDialog(parent),
    ui(new Ui::AlarmDialog)
{
    mpEventLogger = evlog;
    ui->setupUi(this);
    model = new TemperatureAlarmListModel(this);
    ui->alarmlistView->setModel(model);
    connect(mpEventLogger, SIGNAL(tresholdCrossed(QString)), model,
            SLOT(onTresholdCrossed(QString)));

}

AlarmDialog::~AlarmDialog()
{
    delete ui;
    delete model;
}
