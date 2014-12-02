#ifndef HTTPDAEMON_H
#define HTTPDAEMON_H

#include <QTcpServer>
#include <QAbstractSocket>
#include "filehandler.h"

class HttpDaemon : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpDaemon( QObject *parent = 0);
    ~HttpDaemon();

signals:

public slots:
     void incomingConnection();
     void readClient();
     void discardClient();
     void on_tcp_socket_event(QAbstractSocket::SocketState socketState);



private:

     void pause();
     void resume();
     const char * getTextForEnum( int enumval );
     bool disabled;
     FileHandler *mpFH;
     int mPort;



};

#endif // HTTPDAEMON_H
