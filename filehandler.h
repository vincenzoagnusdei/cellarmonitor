#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QFile>
#include <QTextStream>
#include <QString>





class FileHandler
{


public:

    static const QString THRESHOLDS_FILE;    
    static const QString MONITOR_STATUS_FILE;

    FileHandler();
    ~FileHandler();

    int writeThresholds(QString *thresholds=NULL);
    int readThresholds(QStringList *vals);    
    int readMonitorStatus(QStringList *vals);
    int writeMonitorStatus(QString *data);



private:




};

#endif // FILEHANDLER_H
