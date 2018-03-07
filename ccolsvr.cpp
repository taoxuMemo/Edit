#include "ccolsvr.h"
#include "ctool.h"
CColSvr::CColSvr()
{

}
bool CColSvr::setData(char *pData, int nLen)
{
    if(*pData++!='#' || *pData++!='#')
    {
        m_nErrCode=1;   //包头错误
        return false;
    }

    char sLen[5];
    strncpy(sLen,pData,4);
    sLen[4]=NULL;
    int nSJDLen=atoi(sLen);
    if(nLen!=nSJDLen+12)
    {
        m_nErrCode=2;   //数据段长度错误
        return false;
    }
    pData+=4;

    char sCRC[5];
    strncpy(sCRC,pData+nSJDLen,4);
    sCRC[4]=NULL;
    int nCRC=atoi(sCRC);
    unsigned int nDataCRC=CTool::CRC16_Checkout((unsigned char *)pData,(unsigned int)nSJDLen);
    if(nCRC!=nDataCRC)
    {
        m_nErrCode=3;   //校验错误
        return false;
    }

    if(*(pData+nSJDLen+4)!=0x0d || *(pData+nSJDLen+5)!=0x0a)
    {
        m_nErrCode=4;   //包尾错误
        return false;
    }


    if(*pData++!='S' || *pData++!='T' ||*pData++!='=')
    {
        m_nErrCode=5;   //ST字段错误
        return false;
    }

    m_nST=CTool::strtoint(pData,2);
    if(m_nST==-1)
    {
        m_nErrCode=6;   //ST码非数字
        return false;
    }
    pData+=3;

    if(*pData++!='C' || *pData++!='N' ||*pData++!='=')
    {
        m_nErrCode=7;   //CN字段错误
        return false;
    }
    m_nCN=CTool::strtoint(pData,4);
    if(m_nCN==-1)
    {
        m_nErrCode=8;   //CN码非数字
        return false;
    }
    pData+=5;

    if(*pData++!='C' || *pData++!='P' ||*pData++!='='|| *pData++!='&' ||*pData++!='&')
    {
        m_nErrCode=9;   //CP字段错误
        return false;
    }

    m_nArea=nSJDLen-5-1-7-1-3-2-2;//分别减去st ; cn ; cp= && && CRC 换行回车
    strncpy(m_sData,pData,m_nArea);

    return true;
}
QList<stuCol>   CColSvr::getlist()
{
    QList<stuCol> relist;
    if(m_nCN==2011)
    {
        QString str=QString(QLatin1String(m_sData));
        QStringList sl=str.split(",");
        for(int i=0;i<sl.size();i++)
        {

            QString str1=sl.at(i);
            QStringList sl1=str1.split("-");
            if(sl1.size()!=2)
            {
                m_nErrCode=101;
                continue;
            }
            QString sName=sl1.at(0);
            stuCol stu;
            QByteArray ba=sName.toLatin1();
            strncpy(stu.sName,ba.data(),ba.size());

            QString sTypeVal=sl1.at(1);
            QStringList sl2=sTypeVal.split("=");
            if(sl2.size()!=2)
            {
                m_nErrCode=102;
                continue;
            }

            QString sType=sl2.at(0);
            QByteArray ba1=sType.toLatin1();
            strncpy(stu.sType,ba1.data(),ba1.size());

            QString sVal=sl2.at(1);
            stu.dvalue=sVal.toDouble();
            if(stu.dvalue==0)
                continue;
            relist.append(stu);
        }
        return relist;
    }
}
