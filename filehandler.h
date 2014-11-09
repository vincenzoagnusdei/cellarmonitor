#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QFile>
#include <QTextStream>
#include <QString>





class FileHandler
{


public:

    static const QString THRESHOLDS_FILE;

    FileHandler();
    ~FileHandler();

    int writeThresholds(QString *thresholds=NULL);
    int readThresholds(QStringList *vals);



private:




};

#endif // FILEHANDLER_H
