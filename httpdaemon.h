#ifndef HTTPDAEMON_H
#define HTTPDAEMON_H

#include <QTcpServer>
#include <QAbstractSocket>
#include "filehandler.h"
#include <QTcpSocket>
#include <eventlogger.h>

class HttpDaemon : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpDaemon( QObject *parent = 0);
    ~HttpDaemon();
    bool writeData(QStringList data);

    static const QString GET_FILE_LIST;
    static const QString GET_DATETIME;


signals:
    // void dataReceived();
    void error(QTcpSocket::SocketError socketError);
    void stateChanged(QAbstractSocket::SocketState ss);
public slots:
     void incomingConnection();   
     void readClient();
     void discardClient();
     void on_tcp_socket_event(QAbstractSocket::SocketState ss);
     void on_error(QTcpSocket::SocketError socketError);



private:

     const char * getTextForEnum( int enumval );
     bool writeData(QString data);
     FileHandler *mpFH;
     EventLogger *mpEventLogger;
     int mPort;



};

#endif // HTTPDAEMON_H
