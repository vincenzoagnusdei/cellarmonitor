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

    ui->spinBoxHumMin->setValue((vals.at(hummin)).toInt());
    ui->spinBoxHumMax->setValue((vals.at(hummax)).toInt());
    ui->spinBoxHumTime->setValue((vals.at(humtime)).toInt());

    ui->spinBoxLumMin->setValue((vals.at(lummin)).toInt());
    ui->spinBoxLumMax->setValue(vals.at(lummax).toInt());
    ui->spinBoxLumTime->setValue(vals.at(lumtime).toInt());

    ui->spinBoxTempMin->setValue((vals.at(tempmin)).toInt());
    ui->spinBoxTempMax->setValue((vals.at(tempmax)).toInt());
    ui->spinBoxTempTime->setValue((vals.at(temptime)).toInt());
    }

    return 1;
}




