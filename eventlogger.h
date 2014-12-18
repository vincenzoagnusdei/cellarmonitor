#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <QObject>
#include <QString>

class EventLogger : public QObject
{
    Q_OBJECT


public:

    enum EVENT_TYPE_ENUM {HUMIDITY_MIN_TH, HUMIDITY_MAX_TH, HUMIDITY_VAL, TEMPERATURE_MIN_TH, TEMPERATURE_MAX_TH,
                          TEMPERATURE_VAL, LUMINOSITY_MIN_TH, LUMINOSITY_MAX_TH, LUMINOSITY_VAL };

    static const int LENGHT_LINE;
    static const QString LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_A;
    static const QString LOG_MIN_TEMPERATURE_TH_CROSSED_FILE_B;
    static const QString LOG_MIN_HUMIDITY_TH_CROSSED_FILE_A;
    static const QString LOG_MIN_HUMIDITY_TH_CROSSED_FILE_B;
    static const QString LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_A;
    static const QString LOG_MIN_LUMINOSITY_TH_CROSSED_FILE_B;

    static const QString LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_A;
    static const QString LOG_MAX_TEMPERATURE_TH_CROSSED_FILE_B;
    static const QString LOG_MAX_HUMIDITY_TH_CROSSED_FILE_A;
    static const QString LOG_MAX_HUMIDITY_TH_CROSSED_FILE_B;
    static const QString LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_A;
    static const QString LOG_MAX_LUMINOSITY_TH_CROSSED_FILE_B;

    static const QString LOG_TEMPERATURE_CURRENT_VALUE_FILE_A;
    static const QString LOG_TEMPERATURE_CURRENT_VALUE_FILE_B;
    static const QString LOG_HUMIDITY_CURRENT_VALUE_FILE_A;
    static const QString LOG_HUMIDITY_CURRENT_VALUE_FILE_B;
    static const QString LOG_LUMINOSITY_CURRENT_VALUE_FILE_A;
    static const QString LOG_LUMINOSITY_CURRENT_VALUE_FILE_B;
    static const int LOG_SIZE;

    explicit EventLogger(QObject *parent = 0);
    int writeEvent(QString, EVENT_TYPE_ENUM);
    int readAllEventThresholds(QStringList *, EVENT_TYPE_ENUM);
    QStringList getFileInfoUpdate();

private:

    void trunkateFile(QString filename);
    QString getFileLogName(EVENT_TYPE_ENUM evtype);
    void getFileNames(EVENT_TYPE_ENUM evtype, QString *filenamea, QString  *filenameb);
    QString mLogTemperatureThXFile;
    QString mLogHumidityThXFile;
    QString mLogLuminosityThXFile;
    QString mLogCurrValueTemperatureFile;
    QString mLogCurrValueHumidityFile;
    QString mLogCurrValueLuminosityFile;
    QString prepareAlarmEventForGUI(float, float , QString, EVENT_TYPE_ENUM );
    QString prepareEventForFile(float, float, QString, EVENT_TYPE_ENUM);


signals:

    void tresholdCrossed(QString);
    void currentValue(QString);




public slots:

    void onMinThresholdCrossed(float, float, QString, EventLogger::EVENT_TYPE_ENUM );
    void onMaxThresholdCrossed(float, float, QString, EventLogger::EVENT_TYPE_ENUM );
    void onCurrentValue(float, QString , EventLogger::EVENT_TYPE_ENUM );



};

#endif // EVENTLOGGER_H
