#include "cnetconthread.h"

CNetConThread::CNetConThread(QObject *parent): QThread(parent)
{
    m_Main=(MainWindow*)parent;
}
void CMySocketThread::stop()
{
    m_isrun=false;
}
void CMySocketThread::run()
{
    m_isrun=true;
    while(m_isrun)
    {
        sleep(1);
        for(int i=0;i<6;i++)
        {
            if(m_Main->m_pMySocket[i]!=NULL)
            {
                if(m_Main->m_pMySocket[i]->isConnect==false)
                {
                    if(m_Main->m_pMySocket[i]->MyConnect()==-1)
                    {
                        //  QString(m_Main->m_pMySocket[i]->m_IPAddr.sIP)
                        QString str="连接成功----"+QString(m_Main->m_pMySocket[i]->m_IPAddr.sIP)+":"+QString::number(m_Main->m_pMySocket[i]->m_IPAddr.nPort);
                        emit TestSignal(str);
                    }
                }
            }
        }
    }
}
