#include "cserialthread.h"
#include "mainwindow.h"
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>

#include "common.h"
//#include "tty.h"

#ifdef __cplusplus
extern "C"
{
#endif

int		tty_init(const char * tty);
int 	tty_setting(int fd, int bitrate, int datasize, int mode, int flow, int par, int stop);
int		tty_write(int fd, char *frame, int len);
int		tty_read(int fd, char *frame);
#ifdef __cplusplus
}
#endif


CSerialThread::CSerialThread(QObject *parent): QThread(parent)
{
    m_Main=(MainWindow*)parent;
    m_fd=-1;
    memset(m_sData,0,2048);
}
void CSerialThread::stop()
{
    m_isrun=false;
}
void CSerialThread::run()
{
    m_isrun=true;
    while(m_isrun)
    {
        QString strData;
        RecvData(strData);
        while(m_list.size()>0)
        {
            QString strData=m_list.removeAt(0);
            m_Main->RecvData(strData.toLatin1());
        }
        msleep(100);
    }
}
bool CSerialThread::SetParam(QString name, int nbaud)
{
    QString strErr;
    m_fd = tty_init(name.toLatin1().data());
    if( m_fd < 0){s
                strErr="Initialize tty device "+name+" failed!";
        //    m_pMain->addList(strErr);
        return false;
    }
    int  ret= tty_setting(m_fd, nbaud, 8, 1, 0, 'n', 1);
    if(ret < 0){
        strErr="setting tty device "+name+" failed!";
        //    m_pMain->addList(strErr);
        return false;
    }
    return true;
}
bool CSerialThread::SendData(QString sData)
{
    QString strErr;
    if(m_fd==-1)
    {
        strErr="Serial not open!!!!";
        //    m_pMain->addList(strErr);
        return false;
    }
    QByteArray ba=sData.toLatin1();
    int ret = tty_write(m_fd , ba.data(), ba.size());
    if(ret <= 0){

        strErr="Write tty device failed!";
        //    m_pMain->addList(strErr);
        close(m_fd);
        return false;
    }
    sleep(1);
    return true;
}
bool CSerialThread::RecvData(QString &sData)
{
    if(m_fd<0)
        return false;
    QString strE,strData;
    char sD[2048],sDD[2048];
    memset(sD,0,2048);
    memset(sDD,0,2048);
    int ret=tty_read(m_fd, sD);

    //    QString strData=QString(QLatin1String(sD));
    if(ret > 0 ){
        // got data success
        //        strE="RECV:"+strData;
        //        m_pMain->addList(strE);
        //   char *pData=sDD;
        //   int loc=0;
        for(int i=0,loc=0;i<ret;i++,loc++)
        {
            if(sD[i]=='\n' && sD[i+1]=='\r')
            {
                sDD[loc]=sD[i];
                sDD[loc+1]=sD[i+1];
                m_strData+=QString(QLatin1String(sDD));
                if(m_strData.at(0)=='#' && m_strData.at(1)=='#')
                    m_list.append(m_strData);
                m_strData="";
                memset(sDD,0,2048);
            }
            if(sD[i]=='#' && sD[i+1]=='#')
            {
                loc=0;
                memset(sDD,0,2048);
            }
            sDD[loc]=sD[i];
        }
        if(sDD[0]=='#' &&sDD[1]=='#')
            m_strData+=QString(QLatin1String(sDD));
    }
    else if(ret == 0){
        // Can read data timeout, try again
        //dbg_printf("== select can timout ===\r\n");
        strE="== select can timout ===";
        //   m_pMain->addList(strE);
    }
    else if(ret < 0){
        // Can read data error!
        // dbg_printf("== read can error ===\r\n");
        strE="== read can error ===";
        //    m_pMain->addList(strE);
    }
    sData=strData;
    return true;
}
bool CSerialThread::TestXY(char *pD,int nSize)
{
    QString strE,strData;
    char sD[2048],sDD[2048];
    memset(sD,0,2048);
    memset(sDD,0,2048);
    //  int ret=tty_read(m_fd, sD);
    strncpy(sD,pD,nSize);
    int ret=nSize;
    if(ret > 0 ){
        // got data success
        //        strE="RECV:"+strData;
        //        m_pMain->addList(strE);
        //   char *pData=sDD;
        //   int loc=0;
        for(int i=0,loc=0;i<ret;i++,loc++)
        {
            if(sD[i]=='\n' && sD[i+1]=='\r')
            {
                sDD[loc]=sD[i];
                sDD[loc+1]=sD[i+1];
                m_strData+=QString(QLatin1String(sDD));
                if(m_strData.at(0)=='#' && m_strData.at(1)=='#')
                    m_list.append(m_strData);
                m_strData="";
                memset(sDD,0,2048);
            }
            if(sD[i]=='#' && sD[i+1]=='#')
            {
                loc=0;
                memset(sDD,0,2048);
            }
            sDD[loc]=sD[i];
        }
        if(sDD[0]=='#' &&sDD[1]=='#')
            m_strData+=QString(QLatin1String(sDD));
    }
    return true;
}
