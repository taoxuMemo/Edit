#include "cmysocket.h"

CMySocket::CMySocket()
{
    isConnect=false;
}
bool CMySocket::MyConnect()
{
    host = gethostbyname(m_IPAddr.sIP);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        isConnect=false;
        return false;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(m_IPAddr.nPort);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(serv_addr.sin_zero),8);

    if (connect(sockfd, (struct sockaddr *)&serv_addr,\
    sizeof(struct sockaddr)) == -1) {
        perror("connect");
        isConnect=false;
        return false;
    }
    isConnect=true;
    return true;

//    if(recon==true && isConnect==true)
//    {

//        //close(sockfd);
//        isConnect=false;
//    }
//    if(isConnect)

//        ;//断开连接
//    else
//    {
//        ;
//    }
    return true;
}
bool CMySocket::MySend(char * sData,int nLen)
{
    int sendbytes;
    if ((sendbytes = send(sockfd,sData, nLen, 0)) == -1) {
        perror("send");
        isConnect=false;
        return false;
    }
    return true;
}
int CMySocket::MyRecv(char *sData)
{
    int nLen=recv(sockfd,sData,1024,0);
    if(nLen==-1)
        {
        isConnect=false;
        return -1;
    }
    return nLen;

}
bool CMySocket::SetParam(stuIPAddr stu)
{
    m_IPAddr=stu;
    return true;
}

bool CMySocket::Stop()
{
    if(isConnect==true)
        {
       shutdown(sockfd,SHUT_RDWR);
       isConnect=false;
   //     close(sockfd);
    }
    return true;
}
