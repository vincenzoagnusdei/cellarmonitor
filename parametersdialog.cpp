#include <QStringList>
#include "parametersdialog.h"
#include "ui_parametersdialog.h"
#include "mainwindow.h"


ParametersDialog::ParametersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParametersDialog)
{
    ui->setupUi(this);
    ui->portEdit->setInputMask("0000");
}

ParametersDialog::~ParametersDialog()
{
    delete ui;
}


void ParametersDialog::initParameters(){

    QStringList listparameter;
    mpFH = ((MainWindow *) this->parent())->getFileHanlder();

    mpFH->readParameters(&listparameter);
    ui->portEdit->setText(listparameter.at(FileHandler::PORTNUM));


}




void ParametersDialog::on_buttonBox_accepted()
{

     QString listparameter;
      listparameter.append(ui->portEdit->text());
      mpFH->writeParameters(&listparameter);



}

