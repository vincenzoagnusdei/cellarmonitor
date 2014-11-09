#ifndef THRESHOLDSETUPDIALOG_H
#define THRESHOLDSETUPDIALOG_H

#include <QDialog>
#include <filehandler.h>

namespace Ui {
class ThresholdSetupDialog;
}

class ThresholdSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdSetupDialog(QWidget *parent = 0);
    ~ThresholdSetupDialog();
    int initThresholds();

private slots:
    void on_buttonBox_accepted();

    void on_ThresholdSetupDialog_finished(int result);



private:
    Ui::ThresholdSetupDialog *ui;
    FileHandler mFH;


};

#endif // THRESHOLDSETUPDIALOG_H
