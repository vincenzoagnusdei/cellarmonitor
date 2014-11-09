#include "thresholddialog.h"
#include "ui_thresholddialog.h"
#include <string>
using std::string;




ThresholdDialog::ThresholdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdDialog)
{
    ui->setupUi(this);
}

ThresholdDialog::~ThresholdDialog()
{
    delete ui;
}




void ThresholdDialog::on_buttonBox_accepted()
{

}
