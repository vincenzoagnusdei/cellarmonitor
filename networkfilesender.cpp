#include "networkfilesender.h"
#include <QtNetwork>
#include <QDebug>
#include <QTimer>



static const char * EventEnumStrings[] = { "UnconnectedState","HostLookupState","ConnectingState","ConnectedState","BoundState",
"ListeningState","ClosingState" };


NetworkFileSender::NetworkFileSender(QTcpSocket *tcpsocket, QObject *parent) :
    QThread(parent)
{
    mpTcpSocket = tcpsocket;



}



 void NetworkFileSender::run()
 {


        qDebug() <<  "NetworkFileSender" << currentThreadId();


        connect(mpTcpSocket, SIGNAL(readyRead()), this, SLOT(readClient()), Qt::QueuedConnection);
        connect(mpTcpSocket, SIGNAL(disconnected()), this, SLOT(discardClient()));
        connect(mpTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
                 SLOT(on_tcp_socket_event(QAbstractSocket::SocketState)));
         QTimer timer;
         connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()), Qt::DirectConnection);
         timer.start(5000);

         exec();



 }



 void NetworkFileSender::readClient()
{


    // This slot is called when the client sent data to the server. The
    // server looks if it was a get request and sends a very simple HTML
    // document back.

     qDebug() <<  "NetworkFileSender.readClient" << currentThreadId();

    while (mpTcpSocket->canReadLine()) {
        QStringList tokens = QString(mpTcpSocket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
        if (tokens[0].toLower() == "get") {
            QTextStream os(mpTcpSocket);
            /*
            os.setAutoDetectUnicode(true);
            os << "HTTP/1.0 200 Ok\r\n"
                "Content-Type: text/html; charset=\"utf-8\"\r\n"
                "\r\n"
                "<h1>Nothing to see here</h1>\n"
                << QDateTime::currentDateTime().toString() << "\n";
            socket->close();


            if (socket->state() == QTcpSocket::UnconnectedState) {
                delete socket;
            }
            */
        }
        else if (tokens[0].toLower() == "getdata") {
        {

        }

      }
         qDebug() << tokens[0] << " " << QObject::thread()->objectName();
           qDebug() << tokens[1] << " " << QObject::thread()->objectName();
             qDebug() << tokens[2] << " " << QObject::thread()->objectName();
    }

}


 void NetworkFileSender::discardClient()
{
  // QTcpSocket* socket = (QTcpSocket*)sender();
  mpTcpSocket->deleteLater();

}

 void NetworkFileSender::on_tcp_socket_event(QAbstractSocket::SocketState ss)
 {

     qDebug() << this->getTextForEnum(ss);
 }

 const char * NetworkFileSender::getTextForEnum( int enumval )
 {
   return EventEnumStrings[enumval];
 }


 void NetworkFileSender::onTimeout()
 {
     qDebug()<<"Thread::onTimeout get called from? : "<<QThread::currentThreadId();
 }
