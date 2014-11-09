#include "databackupdialog.h"
#include "ui_databackupdialog.h"

DataBackupDialog::DataBackupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataBackupDialog)
{
    ui->setupUi(this);
}

DataBackupDialog::~DataBackupDialog()
{
    delete ui;
}
