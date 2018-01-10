#ifndef CMYSOCKET_H
#define CMYSOCKET_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include"qdatatype.h"
#define SERVPORT 4444
#define MESSAGE "1234567890"

class CMySocket
{
public:
    CMySocket();
    bool MyConnect(stuIPAddr stu,bool recon); //stu 远程服务器地址  //recon 是否重新连接远程服务器 1重新 0不重新
    bool SetParam(stuIPAddr);
    bool isConnect;
    int sockfd, sendbytes;
    char buf[15] ;
    struct hostent *host;
    struct sockaddr_in serv_addr;
};

#endif // CMYSOCKET_H
