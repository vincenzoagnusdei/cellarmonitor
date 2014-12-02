#include "coapserver.h"
#include <QDebug>
#include <QMutex>
#include "mainwindow.h"
#include <stdlib.h>
#include <stdio.h>


const char* COAPServer::gURIList[NUM_RESOURCES] = {
        "/test",
        "/currenttemperature"
    };


COAPServer::COAPServer(QObject *parent) :
    QThread(parent)
{
    this->initgCallbacks();
}

void COAPServer::initgCallbacks()
{
    gCallbacks[TEST] = gTestCallback;
    gCallbacks[GETTEMPERATURE] = gGetTemperature;
}

void COAPServer::run()
{



    char *listenAddressString = "*";    // default server address is local
    char *listenPortString    = "9999";  // default port must be configurable -AV-
    char buffer[BUF_LEN];
    char uriBuffer[URI_BUF_LEN];
    int recvURILen = 0;

    struct sockaddr_storage recvAddr;   // storage for handling receive address
    socklen_t recvAddrLen = sizeof(struct sockaddr_storage);
    struct sockaddr_in *v4Addr;
    struct sockaddr_in6 *v6Addr;
    char straddr[INET6_ADDRSTRLEN];
    QMutex mutex;
    int sockfd;

    struct addrinfo *bindAddr;  // setup bind address
    CoapPDU *recvPDU=NULL;
    // setup URI callbacks using uthash hash table
    struct URIHashEntry *entry = NULL, *directory = NULL, *hash = NULL;


    qDebug("Setting up bind address");
    int ret = setupAddress(listenAddressString,listenPortString,&bindAddr,SOCK_DGRAM,AF_INET);
    if(ret!=0) {
        qDebug("Error setting up bind address, exiting.");

        mutex.lock();
        this->Stop = true;
        mutex.unlock();

    }
    else
    {

        // iterate through returned structure to see what we got
        printAddressStructures(bindAddr);

        // setup socket
        sockfd = socket(bindAddr->ai_family,bindAddr->ai_socktype,bindAddr->ai_protocol);

        if(bind(sockfd,bindAddr->ai_addr,bindAddr->ai_addrlen)!=0) {

            qDebug("Error binding socket");

            mutex.lock();
            this->Stop = true;
            mutex.unlock();
        }
        else
        {

            printAddress(bindAddr);

            for(int i=0; i<NUM_RESOURCES; i++)
            {
                // create new hash structure to bind URI and callback
                entry = (struct URIHashEntry*)malloc(sizeof(struct URIHashEntry));
                entry->uri = gURIList[i];
                entry->callback = gCallbacks[i];
                // add hash structure to hash table, note that key is the URI
                HASH_ADD_KEYPTR(hh, directory, entry->uri, strlen(entry->uri), entry);
            }


        }
        // reuse the same PDU
        recvPDU = new CoapPDU((uint8_t*)buffer,BUF_LEN,BUF_LEN);
    }

    // just block and handle one packet at a time in a single thread
    // you're not going to use this code for a production system are you ;)
    while(!this->Stop) {
        // receive packet
        ret = recvfrom(sockfd,&buffer,BUF_LEN,0,(sockaddr*)&recvAddr,&recvAddrLen);
        if(ret==-1) {
            qDebug("Error receiving data");
            continue;
        }

        // print src address
        switch(recvAddr.ss_family) {
            case AF_INET:
                v4Addr = (struct sockaddr_in*)&recvAddr;
                qDebug("Got packet from %s:%d",inet_ntoa(v4Addr->sin_addr),ntohs(v4Addr->sin_port));
            break;

            case AF_INET6:
                v6Addr = (struct sockaddr_in6*)&recvAddr;
                qDebug("Got packet from %s:%d",inet_ntop(AF_INET6,&v6Addr->sin6_addr,straddr,sizeof(straddr)),ntohs(v6Addr->sin6_port));
            break;
        }

        // validate packet
        if(ret>BUF_LEN) {
            qDebug("PDU too large to fit in pre-allocated buffer");
            continue;
        }
        recvPDU->setPDULength(ret);
        if(recvPDU->validate()!=1) {
            qDebug("Malformed CoAP packet");
            continue;
        }
        qDebug("Valid CoAP PDU received");
        recvPDU->printHuman();

        // depending on what this is, maybe call callback function
        if(recvPDU->getURI(uriBuffer,URI_BUF_LEN,&recvURILen)!=0) {
            qDebug("Error retrieving URI");
            continue;
        }
        if(recvURILen==0) {
            qDebug("There is no URI associated with this Coap PDU");
        } else {
            HASH_FIND_STR(directory,uriBuffer,hash);
            if(hash) {
                qDebug("Hash id is %d.", hash->id);
                hash->callback(recvPDU,sockfd,&recvAddr, ((MainWindow *) this->parent())->getTemperatureThreadInstance());
                continue;
            } else {
                qDebug("Hash not found.");
                continue;
            }
        }

        // no URI, handle cases

        // code==0, no payload, this is a ping request, send RST
        if(recvPDU->getPDULength()==0&&recvPDU->getCode()==0) {
            qDebug("CoAP ping request");
        }

    }


    if (recvPDU != NULL)
        delete recvPDU;


}


// callback function for test
int gTestCallback(CoapPDU *request, int sockfd, struct sockaddr_storage *recvFrom, MeasuringPointThread* m) {
    socklen_t addrLen = sizeof(struct sockaddr_in);
    if(recvFrom->ss_family==AF_INET6) {
        addrLen = sizeof(struct sockaddr_in6);
    }
    qDebug("gTestCallback function called");

    //  prepare appropriate response
    CoapPDU *response = new CoapPDU();
    response->setVersion(1);
    response->setMessageID(request->getMessageID());
    response->setToken(request->getTokenPointer(),request->getTokenLength());
    //response->setToken((uint8_t*)"\1\16",2);

    char payload[10];

    sprintf(payload, "%d",  m->getValue());

    // respond differently, depending on method code
    switch(request->getCode()) {
        case CoapPDU::COAP_EMPTY:
            // makes no sense, send RST
        break;
        case CoapPDU::COAP_GET:
            response->setCode(CoapPDU::COAP_CONTENT);
            response->setContentFormat(CoapPDU::COAP_CONTENT_FORMAT_TEXT_PLAIN);
            response->setPayload((uint8_t*)payload,strlen(payload));
        break;
        case CoapPDU::COAP_POST:
            response->setCode(CoapPDU::COAP_CREATED);
        break;
        case CoapPDU::COAP_PUT:
            response->setCode(CoapPDU::COAP_CHANGED);
        break;
        case CoapPDU::COAP_DELETE:
            response->setCode(CoapPDU::COAP_DELETED);
            response->setPayload((uint8_t*)"DELETE OK",9);
        break;
        default:
        break;
    }

    // type
    switch(request->getType()) {
        case CoapPDU::COAP_CONFIRMABLE:
            response->setType(CoapPDU::COAP_ACKNOWLEDGEMENT);
        break;
        case CoapPDU::COAP_NON_CONFIRMABLE:
            response->setType(CoapPDU::COAP_ACKNOWLEDGEMENT);
        break;
        case CoapPDU::COAP_ACKNOWLEDGEMENT:
        break;
        case CoapPDU::COAP_RESET:
        break;
        default:
            delete response;
            return 1;
        break;
    };

    // send the packet
    ssize_t sent = sendto(
        sockfd,
        response->getPDUPointer(),
        response->getPDULength(),
        0,
        (sockaddr*)recvFrom,
        addrLen
    );
    if(sent<0) {
        qDebug("Error sending packet: %ld.",sent);
        delete response;
        return 1;
    } else {
        qDebug("Sent: %ld",sent);
    }

    delete response;
    return 0;
}



extern "C" int call_M_getValue(MeasuringPointThread* m) {
    return m->getValue();
}

int gGetTemperature(CoapPDU *request, int sockfd, struct sockaddr_storage *recvFrom, MeasuringPointThread* m) {
    socklen_t addrLen = sizeof(struct sockaddr_in);
    if(recvFrom->ss_family==AF_INET6) {
        addrLen = sizeof(struct sockaddr_in6);
    }
    qDebug("gGetTemperature function called");

    //  prepare appropriate response
    CoapPDU *response = new CoapPDU();
    response->setVersion(1);
    response->setMessageID(request->getMessageID());
    response->setToken(request->getTokenPointer(),request->getTokenLength());
    //response->setToken((uint8_t*)"\1\16",2);

    char payload[10];

    sprintf(payload, "%d",  m->getValue());


    // respond differently, depending on method code
    switch(request->getCode()) {
        case CoapPDU::COAP_EMPTY:
            // makes no sense, send RST
        break;
        case CoapPDU::COAP_GET:
            response->setCode(CoapPDU::COAP_CONTENT);
            response->setContentFormat(CoapPDU::COAP_CONTENT_FORMAT_TEXT_PLAIN);
            response->setPayload((uint8_t*)payload,strlen(payload));
        break;
        case CoapPDU::COAP_POST:
            response->setCode(CoapPDU::COAP_CREATED);
        break;
        case CoapPDU::COAP_PUT:
            response->setCode(CoapPDU::COAP_CHANGED);
        break;
        case CoapPDU::COAP_DELETE:
            response->setCode(CoapPDU::COAP_DELETED);
            response->setPayload((uint8_t*)"DELETE OK",9);
        break;
        default:
        break;
    }

    // type
    switch(request->getType()) {
        case CoapPDU::COAP_CONFIRMABLE:
            response->setType(CoapPDU::COAP_ACKNOWLEDGEMENT);
        break;
        case CoapPDU::COAP_NON_CONFIRMABLE:
            response->setType(CoapPDU::COAP_ACKNOWLEDGEMENT);
        break;
        case CoapPDU::COAP_ACKNOWLEDGEMENT:
        break;
        case CoapPDU::COAP_RESET:
        break;
        default:
            delete response;
            return 1;
        break;
    };

    // send the packet
    ssize_t sent = sendto(
        sockfd,
        response->getPDUPointer(),
        response->getPDULength(),
        0,
        (sockaddr*)recvFrom,
        addrLen
    );
    if(sent<0) {
        qDebug("Error sending packet: %ld.",sent);
        delete response;
        return 1;
    } else {
        qDebug("Sent: %ld",sent);
    }

    delete response;
    return 0;
}

