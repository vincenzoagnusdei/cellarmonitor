#include "thresholdlogdialog.h"
#include "ui_thresholdlogdialog.h"
#include <QDebug>


const int ThresholdLogDialog::COLUMNS = 4;
const int ThresholdLogDialog::DATE_COL=0;
const int ThresholdLogDialog::MEASURE_COL=1;
const int ThresholdLogDialog::THRESHOLD_COL=2;
const int ThresholdLogDialog::SENSOR_COL=3;


ThresholdLogDialog::ThresholdLogDialog(QWidget *parent, EventLogger *evtlogger) :
    QDialog(parent),
    ui(new Ui::ThresholdLogDialog)
{

    ui->setupUi(this);
    mpEventLogger = evtlogger;

    int rows;

    this->mColumnHeader = QStringList() << "Date" << "Measure"  << "Threshold" << "Sensor";

    int ret = mpEventLogger->readAllEventThresholds(&mVals, EventLogger::TEMPERATURE_MAX_TH);
    if (ret == -1)
    {
        rows=0;
    }
    else
    {
        rows = mVals.size()/COLUMNS;
    }

    model = new QStandardItemModel(rows,COLUMNS,this);
    model->setHorizontalHeaderLabels(mColumnHeader);

    for (int r=0; r < rows ; r++)
    {
        for (int c=0; c < COLUMNS ; c++)
        {
            QModelIndex index = model->index(r,c,QModelIndex());
            model->setData(index,mVals.at(c+(COLUMNS*r)));
        }

    }

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(DATE_COL,130);
    ui->tableView->setColumnWidth(MEASURE_COL,70);
    ui->tableView->setColumnWidth(THRESHOLD_COL,80);
    ui->tableView->setColumnWidth(SENSOR_COL,80);

}

ThresholdLogDialog::~ThresholdLogDialog()
{
    delete ui;
    delete model;
}

