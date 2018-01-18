#include "cprotocol.h"
#include "ctool.h"
#include"qdatatype.h"
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
    if(nCRC!=CTool::CRC16_Checkout((unsigned char *)sData,len));
    {
        return false;
    }

    //判断包尾
    if(*pData++!=0x0d || *pData!=0x0a)
    {
        return false;
    }
    return true;
}
