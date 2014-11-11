#ifndef DIALOGMONITORCONTROL_H
#define DIALOGMONITORCONTROL_H

#include <QDialog>

namespace Ui {
class DialogMonitorControl;
}

class DialogMonitorControl : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMonitorControl(QWidget *parent = 0);
    ~DialogMonitorControl();

private:
    Ui::DialogMonitorControl *ui;
};

#endif // DIALOGMONITORCONTROL_H
