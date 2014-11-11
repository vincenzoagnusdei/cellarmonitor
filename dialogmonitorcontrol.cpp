#include "dialogmonitorcontrol.h"
#include "ui_dialogmonitorcontrol.h"

DialogMonitorControl::DialogMonitorControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMonitorControl)
{
    ui->setupUi(this);
}

DialogMonitorControl::~DialogMonitorControl()
{
    delete ui;
}
