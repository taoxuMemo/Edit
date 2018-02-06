#include "cprotocol.h"
#include "ctool.h"
#include"qdatatype.h"
#include"ctool.h"
#include "mainwindow.h"
CProtocol::CProtocol(QObject *parent) : QObject(parent)
{
    m_pMain=(MainWindow *)parent;
}
//fanhuishujuduanchangdu
int CProtocol::PackageCheck(char * pData, int nLen)
{
    //判断包头
    if(*pData++!='#' || *pData++!='#')
    {
        COperationConfig::writelog(ERRORPACKAGEHEAD);
        return -1;
    }

    //判断长度
    int len=0;
    for(int i=0;i<DATALENGTH;i++)
    {
        len*=10;
        int a=CTool::chartoint(*pData++);
        if(a==-1)
        {
            COperationConfig::writelog(ERRORPACKAGELENTYPE);
            return -1;
        }
        len+=a;
    }
    if(nLen!=(len+PACKAGEHEAD+PACKAGETAIL+CRCLENGTH+DATALENGTH))
    {
        COperationConfig::writelog(ERRORPACKAGELEN);
        return -1;
    }
   // pData++;
    //提取系统编码ST
    char *pST=pData+SJDJGZCB_QQBM_LEN+1;
    if(!(*pST++=='S' && *pST++=='T' && *pST++=='='))
    {
        //系统编码位置错误
        COperationConfig::writelog(ERRORPACKAGEST);
        return -1;
    }

    int nST=(CTool::chartoint(*pST++)*10)+CTool::chartoint(*pST++);
//    pData-=SJDJGZCB_QQBM_LEN+1;
    //判断CRC
    //  char sData[1500];
    //    memset(m_sData,0,1500);
    //    memcpy(m_sData,pData,len);
    unsigned int nDataCRC=CTool::CRC16_Checkout((unsigned char *)pData,(unsigned int)len);
    pData+=len;
    unsigned int nCRC=0;
    for(int i=0;i<CRCLENGTH;i++)
    {
        nCRC<<=4;
        int a=CTool::chartohex(*pData++);
        if(a==-1)
        {
            COperationConfig::writelog(ERRORPACKAGECRCTYPE);
            return -1;
        }
        nCRC|=a;
    }
    if(nCRC!=nDataCRC)
    {
        COperationConfig::writelog(ERRORPACKAGECRC);
        return -1;
    }

    //判断包尾
    if(*pData++!=0x0d || *pData!=0x0a)
    {
        COperationConfig::writelog(ERRORPACKAGETAIL);
        return -1;
    }

    //    char *ppData=m_sData;
    //    ppData+=SJDJGZCB_QQBM_LEN;
    //    if(!(*ppData++=='S' && *ppData++=='T' && *ppData++=='='))
    //    {
    //        //系统编码位置错误
    //        return false;
    //    }
    //    int nXTBM=(CTool::chartoint(*ppData++)*10)+CTool::chartoint(*ppData++);

    //    switch(nXTBM)
    //    {
    //    case XTBMB_DBSZLJC_NO:
    //        break;
    //    case XTBMB_KQZLJC_NO:
    //        break;
    //    case XTBMB_SHJZLJC_NO:
    //        break;
    //    case XTBMB_DXSZLJC_NO:
    //        break;
    //    case XTBMB_TRZLJC_NO:
    //        break;
    //    case XTBMB_HSZLJC_NO:
    //        break;
    //    case XTBMB_HFXYJWJC_NO:
    //        break;
    //    case XTBMB_DQHJWRY_NO:
    //        break;
    //    case XTBMB_DBSTHJWRY_NO:
    //        break;
    //    case XTBMB_DXSTHJWRY_NO:
    //        break;
    //    case XTBMB_HYHJWRY_NO:
    //        break;
    //    case XTBMB_TRHJWRY_NO:
    //        break;
    //    case XTBMB_SHJWRY_NO:
    //        break;
    //    case XTBMB_ZDHJWRY_NO:
    //        break;
    //    case XTBMB_FSXHJWRY_NO:
    //        break;
    //    case XTBMB_GDYCWRY_NO:
    //        break;
    //    case XTBMB_DCHJWRY_NO:
    //        break;
    //    case XTBMB_YQPFGCJK_NO:
    //        break;
    //    case XTBMB_WSPFGCJK_NO:
    //        break;
    //    case XTBMB_XTJH_NO:
    //        break;
    //    default:
    //        //请求编码异常
    //        break;
    //    }

    return nST;
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
QByteArray CProtocol::SpellPackage(QString strData)
{
    QByteArray sSpell=strData.toLatin1();
    QString strLen=QString("%1").arg(strData.length(), DATALENGTH, 10, QChar('0'));
    sSpell.prepend(strLen);//添加长度
    sSpell.prepend("##");  //添加包头##
    //添加校验
    QByteArray sCRC=strData.toLatin1();
    int nCRC=CTool::CRC16_Checkout((unsigned char *)sCRC.data(),(unsigned int)sCRC.length());
    QString c=QString("%1").arg(nCRC, CRCLENGTH, 16, QChar('0')).toUpper();
    sSpell.append(c);
    //添加包尾部
    sSpell.append(0x0D);
    sSpell.append(0x0A);
    return sSpell;
}

































