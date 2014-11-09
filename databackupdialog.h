#ifndef DATABACKUPDIALOG_H
#define DATABACKUPDIALOG_H

#include <QDialog>

namespace Ui {
class DataBackupDialog;
}

class DataBackupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataBackupDialog(QWidget *parent = 0);
    ~DataBackupDialog();

private:
    Ui::DataBackupDialog *ui;
};

#endif // DATABACKUPDIALOG_H
