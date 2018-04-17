#include "ccolsvr.h"
#include "ctool.h"
CColSvr::CColSvr()
{
    m_nErrCode=0;
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
    int nCRC=QString(QLatin1String(sCRC)).toInt(Q_NULLPTR,16);
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
            if(sVal.length()>0)
            {
                switch (sVal.at(0).toLatin1()) {
                case 'N':
                    stu.dvalue=1;
                    break;
                case 'F':
                    stu.dvalue=2;
                    break;
                case 'M':
                    stu.dvalue=3;
                    break;
                case 'S':
                    stu.dvalue=4;
                    break;
                case 'D':
                    stu.dvalue=5;
                    break;
                case 'C':
                    stu.dvalue=6;
                    break;
                case 'T':
                    stu.dvalue=7;
                    break;
                case 'B':
                    stu.dvalue=8;
                    break;
                default:
                    stu.dvalue=sVal.toDouble();
                    break;
                }
            }


//            if(stu.dvalue==0)
//                continue;
            relist.append(stu);
        }
        return relist;
    }
}
QList<stuInfo>   CColSvr::getlistinfo()
{

    QList<stuInfo> relist;
    if(m_nCN==3020)
    {
        QString str=QString(QLatin1String(m_sData));
        QStringList sl=str.split(";");
        if(sl.size()!=2)
        {
            m_nErrCode=201;
            return relist;
        }
        QString  str1=sl.at(0);
        QStringList sl1=str1.split("=");
        QString  str12=sl1.at(1);
        if(str12.size()!=6)
        {
            m_nErrCode=202;
            return relist;
        }


        QString  str2=sl.at(1);
        QStringList sl2=str2.split("=");
        for(int i=0;i<sl2.size();i++)
        {
            stuInfo stu;
            QString     str21=sl2.at(i);
            QStringList sl21=str21.split("-");
            if(sl21.size()!=2)
            {
                m_nErrCode=203;
                continue;
            }
            QString     str211=sl21.at(0);//信息编码
            if(str211.size()!=6)
            {
                m_nErrCode=204;
                continue;
            }
            QString     str212=sl21.at(1);
            QStringList sl212=str212.split("=");
            if(sl212.size()!=2)
            {
                m_nErrCode=205;
                continue;
            }
            QString     str2121=sl212.at(0);
            QString     str2122=sl212.at(1);   //值
            if(str2122.size()>10)
            {
                m_nErrCode=206;
                continue;
            }
            strncpy(stu.sName,str12.toLatin1().data(),6);
            strncpy(stu.sType,str211.toLatin1().data(),6);
            strncpy(stu.sValue,str2122.toLatin1().data(),10);
            relist.append(stu);
        }
        return relist;
    }
}



bool CColSvr::GetSZLStr(int nPort, bool bMark, QString sCoding, QString sPol)
{
    if(m_strSetting.size()!=0)
    {
        m_strSetting+=";";
    }
    m_strSetting+=QString::number(nPort+20)+","+QString::number(bMark)+",";
    return true;
}
bool CColSvr::GetMNLStr(int nPort, bool bMark, int nType)
{
    if(m_strSetting.size()!=0)
    {
        m_strSetting+=";";
    }
    m_strSetting+=QString::number(nPort+30)+","+QString::number(bMark)+","+QString::number(nType);
    return true;
}
bool CColSvr::GetKGLStr(int nPort, int nType)
{
    if(m_strSetting.size()!=0)
    {
        m_strSetting+=";";
    }
    m_strSetting+=QString::number(nPort+20)+","+QString::number(nType);
    return true;
}
