#ifndef COAPSERVER_H
#define COAPSERVER_H

#define __USE_POSIX 1
#include <QThread>
#include <cantcoap/cantcoap.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <math.h>
#include "nethelper.h"
#include "uthash.h"
#include "measuringpoint.h"

#define NUM_RESOURCES 2

// buffers for UDP and URIs
#define BUF_LEN 500
#define URI_BUF_LEN 32


 typedef int (*ResourceCallback)(CoapPDU *pdu, int sockfd, struct sockaddr_storage *recvFrom, MeasuringPointThread* m);


int gTestCallback(CoapPDU *request, int sockfd, struct sockaddr_storage *recvFrom, MeasuringPointThread* m);
int gGetTemperature(CoapPDU *request, int sockfd, struct sockaddr_storage *recvFrom, MeasuringPointThread* m);

extern "C" int call_MeasuringPointThread_getValue(MeasuringPointThread m);



class COAPServer : public QThread
{
    Q_OBJECT
public:
    explicit COAPServer(QObject *parent = 0);

    /* Flag to control COAPServer Thread loop */
    bool Stop;


  signals:

public slots:

protected:
    void run();

private:

    enum CALLBACK {TEST,GETTEMPERATURE};

    // using uthash for the URI hash table. Each entry contains a callback handler.
    struct URIHashEntry {
        const char *uri;
         ResourceCallback callback;
        int id;
        UT_hash_handle hh;
    };



    static const char *gURIList[NUM_RESOURCES];


    // URIs mapped to callback functions here
    ResourceCallback gCallbacks[NUM_RESOURCES];

    static const int gNumResources;

    void initgCallbacks();



};

#endif // COAPSERVER_H
