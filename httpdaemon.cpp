#include "httpdaemon.h"
#include "mainwindow.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QDateTime>
#include <QDebug>
#include <QAbstractSocket>
#include <QStringList>
#include <networkfilesender.h>


/* get filelist \n -> name,date,time */
/* getdata filename -> data */




const QString HttpDaemon::GET_FILE_LIST = "getfilelist";
const QString HttpDaemon::GET_DATETIME = "getdatetime";


static const char * EventEnumStrings[] = { "UnconnectedState","HostLookupState","ConnectingState","ConnectedState","BoundState",
"ListeningState","ClosingState" };




HttpDaemon::HttpDaemon(QObject* parent)
 : QTcpServer(parent)
{
    QStringList param;
    mpFH = ((MainWindow* )parent)->getFileHanlder();
    mpEventLogger = ((MainWindow* )parent)->getEventLoggerHanlder();
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
    connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
             SLOT(on_tcp_socket_event(QAbstractSocket::SocketState)));


}

HttpDaemon::~HttpDaemon()
{

    close();
}

void HttpDaemon::incomingConnection()
{

     QTcpSocket *clientConnection = this->nextPendingConnection();
     connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));

 }



void HttpDaemon::readClient()
{
    QStringList fileinfoupdate;


   QTcpSocket* socket = (QTcpSocket*)sender();
   if (socket->canReadLine())
   {
       QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
       if (tokens[0].toLower() == GET_FILE_LIST)
       {

           fileinfoupdate=mpEventLogger->getFileInfoUpdate();
           this->writeData(fileinfoupdate);

            // emit dataReceived();
        }
    }

}






void HttpDaemon::discardClient()
{

 this->deleteLater();

}



void HttpDaemon::on_tcp_socket_event(QAbstractSocket::SocketState ss)
{

    qDebug() << this->getTextForEnum(ss);
}

const char * HttpDaemon::getTextForEnum( int enumval )
{
  return EventEnumStrings[enumval];
}


void HttpDaemon::on_error(QTcpSocket::SocketError socketError)
{
    qDebug() << socketError;
}




bool HttpDaemon::writeData(QStringList data)
{

    QTcpSocket* socket = (QTcpSocket*)sender();

    QByteArray databyte;
    databyte.append(GET_FILE_LIST);
    databyte.append(" ");
    for (int i=0;i < data.size(); i++)
    {
        databyte.append(data.at(i));
    }

    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(databyte);
        return socket->waitForBytesWritten();
    }
    else
    {
        qDebug() << "Error writing data on socket " << socket->socketDescriptor();
        return false;
    }
}


