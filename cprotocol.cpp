#include "cprotocol.h"
#include "ctool.h"
#include"qdatatype.h"
#include"ctool.h"
CProtocol::CProtocol(QObject *parent) : QObject(parent)
{

}
bool CProtocol::PackageCheck(char * pData, int nLen)
{
    //判断包头
    if(*pData++!='#' || *pData++!='#')
    {
        return false;
    }

    //判断长度
    int len=0;
    for(int i=0;i<DATALENGTH;i++)
    {
        len*=10;
        int a=CTool::chartoint(*pData++);
        if(a==-1)
        {
            return false;
        }
        len+=a;
    }
    if(nLen!=(len+PACKAGEHEAD+PACKAGETAIL+CRCLENGTH+DATALENGTH))
    {
        return false;
    }

    //  char sData[1500];
    memset(m_sData,0,1500);
    memcpy(m_sData,pData,len);
    pData+=len;
    //判断CRC
    int nCRC=0;//=CTool::CRC16_Checkout(pData,nLen);
    for(int i=0;i<CRCLENGTH;i++)
    {
        nCRC<<=4;
        int a=CTool::chartohex(*pData++);
        if(a==-1)
        {
            return false;
        }
        nCRC|=a;
    }
    if(nCRC!=CTool::CRC16_Checkout((unsigned char *)pData,len));
    {
        return false;
    }

    //判断包尾
    if(*pData++!=0x0d || *pData!=0x0a)
    {
        return false;
    }

    pData=m_sData;
    pData+=SJDJGZCB_QQBM_LEN;
    if(!(*pData++='S' && *pData++='T' && *pData++='='))
    {
        //系统编码位置错误
        return false;
    }
    int nXTBM=(CTool::chartoint(*pData++)*10)+CTool::chartoint(*pData++);

    switch(nXTBM)
    {
    case XTBMB_DBSZLJC_NO:
        break;
    case XTBMB_KQZLJC_NO:
        break;
    case XTBMB_SHJZLJC_NO:
        break;
    case XTBMB_DXSZLJC_NO:
        break;
    case XTBMB_TRZLJC_NO:
        break;
    case XTBMB_HSZLJC_NO:
        break;
    case XTBMB_HFXYJWJC_NO:
        break;
    case XTBMB_DQHJWRY_NO:
        break;
    case XTBMB_DBSTHJWRY_NO:
        break;
    case XTBMB_DXSTHJWRY_NO:
        break;
    case XTBMB_HYHJWRY_NO:
        break;
    case XTBMB_TRHJWRY_NO:
        break;
    case XTBMB_SHJWRY_NO:
        break;
    case XTBMB_ZDHJWRY_NO:
        break;
    case XTBMB_FSXHJWRY_NO:
        break;
    case XTBMB_GDYCWRY_NO:
        break;
    case XTBMB_DCHJWRY_NO:
        break;
    case XTBMB_YQPFGCJK_NO:
        break;
    case XTBMB_WSPFGCJK_NO:
        break;
    case XTBMB_XTJH_NO:
        break;
    default:
        //请求编码异常
        break;
    }

    return true;
}
int CProtocol::AddPackageCheck(char *pData, int nLen)
{
    char sdata[1500];
    char *pdata=sdata;
    memset(pdata,0,1500);
    //添加包头
    *pdata++='#';
    *pdata++='#';

    //添加长度
    QString b=QString("%1").arg(nLen, DATALENGTH, 10, QChar('0'));
    memcpy(pdata,b.toLatin1().data(),DATALENGTH);
    pdata+=DATALENGTH;
    memcpy(pdata,pData,nLen);
    pdata+=nLen;

    //添加校验
    int nCRC=CTool::CRC16_Checkout((unsigned char *)pData,(unsigned int)nLen);
    QString c=QString("%1").arg(nCRC, CRCLENGTH, 16, QChar('0')).toUpper();
    memcpy(pdata,c.toLatin1().data(),CRCLENGTH);
    pdata+=CRCLENGTH;

    //添加包尾
    *pdata++=0x0D;
    *pdata++=0x0A;

    memcpy(pData,pdata,nLen+PACKAGEHEADTAIL);
    return nLen+PACKAGEHEADTAIL;
}


































