#include "httpdaemon.h"
#include "mainwindow.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QDateTime>
#include <QDebug>
#include <QAbstractSocket>



static const char * EventEnumStrings[] = { "UnconnectedState","HostLookupState","ConnectingState","ConnectedState","BoundState",
"ListeningState","ClosingState" };

// HttpDaemon is the the class that implements the simple HTTP server.

HttpDaemon::HttpDaemon(QObject* parent)
 : QTcpServer(parent), disabled(false)
{
    QStringList param;
    mpFH = ((MainWindow* )parent)->getFileHanlder();
    mpFH->readParameters(&param);
    mPort = param.at(FileHandler::PORTNUM).toInt();
    if (!listen(QHostAddress::Any, mPort))
    {
        qDebug() << "Error Starting TCPServer";
    }


    if (!this->isListening())
    {
        qDebug("Failed to bind to port");
    }

    connect(this, SIGNAL(newConnection()), this, SLOT(incomingConnection()));

}

HttpDaemon::~HttpDaemon()
{

    close();
}

void HttpDaemon::incomingConnection()
{
     if (disabled)
         return;

     // When a new client connects, the server constructs a QTcpSocket and all
     // communication with the client is done over this QTcpSocket. QTcpSocket
     // works asynchronously, this means that all the communication is done
     // in the two slots readClient() and discardClient().
     QTcpSocket* s = new QTcpSocket(this);
     connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
     connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
     connect(s, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
             SLOT(on_tcp_socket_event(QAbstractSocket::SocketState)));




 }

 void HttpDaemon::pause()
 {
     disabled = true;
 }

 void HttpDaemon::resume()
 {
     disabled = false;
 }


 void HttpDaemon::readClient()
{
    if (disabled)
        return;

    // This slot is called when the client sent data to the server. The
    // server looks if it was a get request and sends a very simple HTML
    // document back.
    QTcpSocket* socket = (QTcpSocket*)sender();
    if (socket->canReadLine()) {
        QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
        if (tokens[0] == "GET") {
            QTextStream os(socket);
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
        }
    }
}

 void HttpDaemon::discardClient()
{
  QTcpSocket* socket = (QTcpSocket*)sender();
  socket->deleteLater();

}

 void HttpDaemon::on_tcp_socket_event(QAbstractSocket::SocketState ss)
 {

     qDebug() << this->getTextForEnum(ss);
 }

 const char * HttpDaemon::getTextForEnum( int enumval )
 {
   return EventEnumStrings[enumval];
 }
