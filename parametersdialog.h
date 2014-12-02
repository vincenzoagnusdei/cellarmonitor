#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>
#include "filehandler.h"

namespace Ui {
class ParametersDialog;
}

class ParametersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParametersDialog(QWidget *parent = 0);
    ~ParametersDialog();

private:
    Ui::ParametersDialog *ui;
    void initParameters();
    FileHandler *mpFH;

private slots:

    void on_buttonBox_accepted();
};

#endif // PARAMETERSDIALOG_H
