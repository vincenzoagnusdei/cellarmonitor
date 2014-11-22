#ifndef COAPSERVER_H
#define COAPSERVER_H

#include <QThread>

class COAPServer : public QThread
{
    Q_OBJECT
public:
    explicit COAPServer(QObject *parent = 0);

signals:

public slots:

};

#endif // COAPSERVER_H
