#include "cmysocket.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include "coperationconfig.h"
CMySocket::CMySocket()
{
    isConnect=false;
}
bool CMySocket::MyConnect()
{


    host = gethostbyname(m_IPAddr.sIP);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        COperationConfig::writelog(ERRNETCREATESOCKET,m_IPAddr.sIP);
        isConnect=false;
        return false;
    }
    /* set socket fd noblock */
    int flag, old_flag;
    old_flag = flag = fcntl(sockfd, F_GETFL, 0);
    flag |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, flag);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(m_IPAddr.nPort);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(serv_addr.sin_zero),8);

    int ref=connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
    if (ref != 0) {
        if(errno==EINPROGRESS)
        {
            struct timeval tm;
            tm.tv_sec = 1;
            tm.tv_usec = 0;
            fd_set set,rset;
            FD_ZERO(&set);
            FD_ZERO(&rset);
            FD_SET(sockfd, &set);
            FD_SET(sockfd, &rset);

            int res;
            res = ::select(sockfd+1, &rset, &set, NULL, &tm);
            if (res < 0) {
               COperationConfig::writelog(ERRNETCONNECTERROR,m_IPAddr.sIP);
            } else if(res == 0) {
               COperationConfig::writelog(ERRNETTIMEOUT,m_IPAddr.sIP);
            } else if (res == 1) {
                if (FD_ISSET(sockfd, &set)) {
                    isConnect=true;
                }
            } else {
                COperationConfig::writelog(ERRNETOTHERERROR,m_IPAddr.sIP);
            }
        }else
        {
            COperationConfig::writelog(ERRNETCREATECON,m_IPAddr.sIP);
        }

    }else
    {
        isConnect=true;
    }

    fcntl(sockfd, F_SETFL, old_flag);

    return isConnect;

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
    fd_set rfds;
    struct timeval timeout = {1, 0};

    FD_ZERO(&rfds);
    FD_SET(sockfd, &rfds);
    int ret=select(sockfd+1, &rfds, NULL, NULL, &timeout);
   // printf("select ret is %d\n",ret);
    if(0 > ret)
    {
        COperationConfig::writelog(ERRRECVSELECT,m_IPAddr.sIP);
        return -1;
    }

    if(0 == ret)
    {
//        printf("time out\n");
        return -2;
    }

    int nLen=recv(sockfd,sData,1024,0);
    if(nLen==0)
    {
        isConnect=false;
        return 0;
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
