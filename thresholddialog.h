#ifndef THRESHOLDDIALOG_H
#define THRESHOLDDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ThresholdDialog;
}

class ThresholdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdDialog(QWidget *parent = 0);
    ~ThresholdDialog();

private slots:

    void on_buttonBox_accepted();

private:
    Ui::ThresholdDialog *ui;   
};

#endif // THRESHOLDDIALOG_H
