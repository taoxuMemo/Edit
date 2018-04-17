#include "cmysocketthread.h"

CMySocketThread::CMySocketThread(QObject *parent): QThread(parent)
{
    //    m_isrun=false;
    //    for(int i=0;i<6;i++)
    //    {
    //        m_ipAddr[i]=null;
    //        isConnect[i]=false;
    //    }
    m_Main=(MainWindow*)parent;
}
void CMySocketThread::stop()
{
    m_isrun=false;
}
bool CMySocketThread::SetParam(stuIPAddr *sid, int num)
{
    //    m_ipAddr[num]=sid;
    //    host[num] = gethostbyname(m_ipAddr[num]->sIP);
    //    if ((sockfd[num] = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    //        //创建网络地址失败
    //        return false;
    //    }
    //    serv_addr[num].sin_family = AF_INET;
    //    serv_addr[num].sin_port = htons(m_ipAddr[num]->nPort);
    //    serv_addr[num].sin_addr = *((struct in_addr *)host->h_addr);
    //    bzero(&(serv_addr[num].sin_zero),8);

    //    /*establish a connection to server*/
    //    if (connect(sockfd[num], (struct sockaddr *)&serv_addr[num],\
    //                sizeof(struct sockaddr)) == -1) {
    //        //连接远程主机失败
    //        return false;
    //    }
    //    isConnect[num]=true;
    return true;
}

void CMySocketThread::run()
{

    m_isrun=true;
    while(m_isrun)
    {

        msleep(200);
        for(int i=0;i<6;i++)
        {
            if(m_Main->m_pMySocket[i]!=NULL &&m_Main->m_pMySocket[i]->isConnect==true)
            {
                char sBuf[1024];
                memset(sBuf,0,1024);
                int nByte=  m_Main->m_pMySocket[i]->MyRecv(sBuf);
                if(nByte>0)
                {
                    QByteArray ba=QByteArray((char*)sBuf,nByte);
                    m_Main->RecvTcpData(ba,i);
                }else if(nByte==0)
                {
                    //断开状态存入数据库
                    m_Main->m_mySql.InsertIPStatus(i,QString(QLatin1String(m_Main->m_pMySocket[i]->m_IPAddr.sIP)),m_Main->m_pMySocket[i]->m_IPAddr.nPort,0);
                }

            }
        }
        if(m_sData.length()==0)
            continue;
        QString str=m_sData.dequeue();
        for(int i=0;i<6;i++)
        {
            if(m_Main->m_pMySocket[i]!=NULL &&m_Main->m_pMySocket[i]->isConnect==true)
            {
                int nByte=  m_Main->m_pMySocket[i]->MySend( str.toLatin1().data(), str.length());
                QString str="断开连接----"+QString(m_Main->m_pMySocket[i]->m_IPAddr.sIP)+":"+QString::number(m_Main->m_pMySocket[i]->m_IPAddr.nPort);
            }
        }
    }
    //                sendbytes[i] = send(sockfd, str.toLatin1().data(), str.length(), 0);
    //                if (sendbytes[i] == -1)
    //                {
    //                    isConnect[i]=false;
    //                }else
    //                {
    //                    ;
    //                }
    //            }
    //        }
    //        emit TestSignal("sdsadsa");
    //        sleep(1);

    //    }
}
