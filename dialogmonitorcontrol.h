#ifndef DIALOGMONITORCONTROL_H
#define DIALOGMONITORCONTROL_H

#include <QDialog>
#include "filehandler.h"

namespace Ui {
class DialogMonitorControl;
}

class DialogMonitorControl : public QDialog
{
    Q_OBJECT

public:    
    static const QString ENABLED;
    static const QString DISABLED;
    explicit DialogMonitorControl(QWidget *parent = 0);
    ~DialogMonitorControl();     
     enum theshold_enum {humidity, luminosity, temperature};

private slots:
     void on_buttonBox_accepted();

signals:
     void monitorControlChanged();

private:
    Ui::DialogMonitorControl *ui;
    FileHandler mFH;
    int initMonitorStatus();
    void checkDiskSpaceForLogEvent();
};

#endif // DIALOGMONITORCONTROL_H
