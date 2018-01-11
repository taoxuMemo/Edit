#include "cmysocketthread.h"

CMySocketThread::CMySocketThread()
{
    m_isrun=false;
    for(int i=0;i<6;i++)
    {
        m_ipAddr[i]=null;
        isConnect[i]=false;
    }
}
void CMySocketThread::stop()
{
    m_isrun=false;
}
bool CMySocketThread::SetParam(stuIPAddr *sid, int num)
{
    m_ipAddr[num]=sid;
    host[num] = gethostbyname(m_ipAddr[num]->sIP);
    if ((sockfd[num] = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        //创建网络地址失败
        return false;
    }
    serv_addr[num].sin_family = AF_INET;
    serv_addr[num].sin_port = htons(m_ipAddr[num]->nPort);
    serv_addr[num].sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(serv_addr[num].sin_zero),8);

    /*establish a connection to server*/
    if (connect(sockfd[num], (struct sockaddr *)&serv_addr[num],\
                sizeof(struct sockaddr)) == -1) {
        //连接远程主机失败
        return false;
    }
    isConnect[num]=true;
    return true;
}

void CMySocketThread::run()
{
    //触发信号
    m_isrun=true;
    while(m_isrun)
    {
        if(m_sData.length()==0)
            continue;
        QString str=m_sData.dequeue();

        for(int i=0;i<6;i++)
        {
            if(isConnect[i]==true)
            {
                sendbytes[i] = send(sockfd, str.toLatin1().data(), str.length(), 0);
                if (sendbytes[i] == -1)
                {
                    isConnect[i]=false;
                }else
                {
                    ;
                }
            }
        }
        emit TestSignal("sdsadsa");
        sleep(1);

    }
}
