#ifndef FILESENDER_H
#define FILESENDER_H

#include <QObject>

class FileSender : public QObject
{
    Q_OBJECT
public:
    explicit FileSender(QObject *parent = 0);

signals:

public slots:
    void on_Data_Received(QString s);


};

#endif // FILESENDER_H
