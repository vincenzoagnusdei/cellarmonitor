#include "thhresholdsdialog.h"
#include "ui_thhresholdsdialog.h"

ThhresholdsDialog::ThhresholdsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThhresholdsDialog)
{
    ui->setupUi(this);
}

ThhresholdsDialog::~ThhresholdsDialog()
{
    delete ui;
}
