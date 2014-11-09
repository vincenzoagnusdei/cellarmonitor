#include "thresholdsetupdialog.h"
#include "ui_thresholdsetupdialog.h"
#include <QTextStream>
#include <QDebug>




ThresholdSetupDialog::ThresholdSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdSetupDialog)
{
    ui->setupUi(this);

   initThresholds();

}

ThresholdSetupDialog::~ThresholdSetupDialog()
{
    delete ui;
}

void ThresholdSetupDialog::on_buttonBox_accepted()
{
    QString str;  

    str= QString("%1").arg(ui->spinBoxHumMin->value());
    str.append(",");
    str.append(QString("%1").arg(ui->spinBoxHumMax->value()));
    str.append(",");
    str.append(QString("%1").arg(ui->spinBoxHumTime->value()));
    str.append(",");


    str.append(QString("%1").arg(ui->spinBoxLumMin->value()));
    str.append(",");
    str.append(QString("%1").arg(ui->spinBoxLumMax->value()));
    str.append(",");
    str.append(QString("%1").arg(ui->spinBoxLumTime->value()));
    str.append(",");

    str.append(QString("%1").arg(ui->spinBoxTempMin->value()));
    str.append(",");
    str.append(QString("%1").arg(ui->spinBoxTempMax->value()));
    str.append(",");
    str.append(QString("%1").arg(ui->spinBoxTempTime->value()));

    if ( mFH.writeThresholds(&str) != 1)
    {
        qDebug() << "Error writing Threhsolds";
    }

}

int ThresholdSetupDialog::initThresholds()
{
    QStringList vals;

    if ( mFH.readThresholds(&vals) != 1)
    {
        qDebug() << "Error reading Threhsolds";
        return -1;
    }
    else
    {



    ui->spinBoxHumMin->setValue((vals.at(0)).toInt());
    ui->spinBoxHumMax->setValue((vals.at(1)).toInt());
    ui->spinBoxHumTime->setValue((vals.at(2)).toInt());

    ui->spinBoxLumMin->setValue((vals.at(3)).toInt());
    ui->spinBoxLumMax->setValue(vals.at(4).toInt());
    ui->spinBoxLumTime->setValue(vals.at(5).toInt());

    ui->spinBoxTempMin->setValue((vals.at(6)).toInt());
    ui->spinBoxTempMax->setValue((vals.at(7)).toInt());
    ui->spinBoxTempTime->setValue((vals.at(8)).toInt());
    }

    return 1;
}

void ThresholdSetupDialog::on_ThresholdSetupDialog_finished(int result)
{
    qDebug() << "on_ThresholdSetupDialog_finished";
}



