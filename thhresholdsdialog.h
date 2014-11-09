#ifndef THHRESHOLDSDIALOG_H
#define THHRESHOLDSDIALOG_H

#include <QDialog>

namespace Ui {
class ThhresholdsDialog;
}

class ThhresholdsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThhresholdsDialog(QWidget *parent = 0);
    ~ThhresholdsDialog();

private:
    Ui::ThhresholdsDialog *ui;
};

#endif // THHRESHOLDSDIALOG_H
