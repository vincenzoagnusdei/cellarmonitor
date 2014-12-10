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
    static const QString PARAMETER_FILE;
    static const QString FILE_DIRECTORY;

    enum parameters_enum {PORTNUM};

    FileHandler();
    ~FileHandler();

    int writeThresholds(QString *thresholds=NULL);
    int readThresholds(QStringList *vals);    
    int readMonitorStatus(QStringList *vals);
    int writeMonitorStatus(QString *data);



private:

    void initParameters(QString *val);

public:
    int readParameters(QStringList *vals);
    int writeParameters(QString *vals);

    QString INIT_MONITOR_STATUS_FILE;
    QString INIT_THRESHOLDS_FILE;


};

#endif // FILEHANDLER_H
