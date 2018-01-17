#ifndef CMYSOCKETTHREAD_H
#define CMYSOCKETTHREAD_H

#include<QThread>
#include<qqueue.h>
#include"qdatatype.h"
#include"sys/socket.h"
#include"netdb.h"
#include "mainwindow.h"
class CMySocketThread : public QThread
{
       Q_OBJECT
public:

    explicit CMySocketThread(QObject *parent = 0);
    void stop();
    bool SetParam(stuIPAddr * sid,int num);
    stuIPAddr *  m_ipAddr[6];

protected:
    void run();
    QQueue<QString> m_sData;
    bool m_isrun;

    bool isConnect[6];
    int sockfd[6], sendbytes[6];
  //  char buf[15] ;
    struct hostent *host[6];
    struct sockaddr_in serv_addr[6];
    MainWindow *m_Main;
signals:
    void TestSignal(QString);
};

#endif // CMYSOCKETTHREAD_H
