#ifndef NETWORKFILESENDER_H
#define NETWORKFILESENDER_H

#include <QThread>
#include <QTcpSocket>

class NetworkFileSender : public QThread
{
    Q_OBJECT
public:
        explicit NetworkFileSender(QTcpSocket *tcpsocket = 0 , QObject *parent = 0);


public slots:

    void readClient();
    void on_tcp_socket_event(QAbstractSocket::SocketState ss);
    void discardClient();
    void onTimeout();



protected:

     void run();

 signals:
     void error(QTcpSocket::SocketError socketError);

 private:

     QTcpSocket *mpTcpSocket;
     const char * getTextForEnum( int enumval );


 };





#endif // NETWORKFILESENDER_H
