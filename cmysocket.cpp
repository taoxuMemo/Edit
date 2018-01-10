#include "cmysocket.h"

CMySocket::CMySocket()
{
    isConnect=false;
}
bool CMySocket::MyConnect(stuIPAddr stu,bool recon)
{
    if(recon==true && isConnect==true)
    {

        //close(sockfd);
        isConnect=false;
    }
    if(isConnect)

        ;//断开连接
    else
    {
        ;
    }
    return true;
}

bool CMySocket::SetParam(stuIPAddr stu)
{
    host = gethostbyname(stu.sIP);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(stu.nPort);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(serv_addr.sin_zero),8);
    return true;
}
