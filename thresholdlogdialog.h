#ifndef THRESHOLDLOGDIALOG_H
#define THRESHOLDLOGDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QStandardItemModel>
#include <QStringList>
#include "eventlogger.h"


namespace Ui {
class ThresholdLogDialog;
}

class ThresholdLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdLogDialog(QWidget *parent = 0, EventLogger *evtlogger=NULL);
    ~ThresholdLogDialog();    
    static const int COLUMNS;

private:
    Ui::ThresholdLogDialog *ui;
    QStandardItemModel *model;
    EventLogger *mpEventLogger;
    QStringList mVals;
    QStringList mColumnHeader;
    static const int DATE_COL;
    static const int MEASURE_COL;
    static const int THRESHOLD_COL;
    static const int SENSOR_COL;



};

#endif // THRESHOLDLOGDIALOG_H
