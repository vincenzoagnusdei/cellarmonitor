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
    enum measuring_point {hummin, hummax, humtime,lummin, lummax, lumtime, tempmin, tempmax, temptime };
    explicit ThresholdSetupDialog(QWidget *parent = 0);
    ~ThresholdSetupDialog();


private slots:
    void on_buttonBox_accepted();

    void on_ThresholdSetupDialog_finished(int result);

signals:
    void thresholdsChanged();

private:
    Ui::ThresholdSetupDialog *ui;
    FileHandler mFH;
    int initThresholds();


};

#endif // THRESHOLDSETUPDIALOG_H
