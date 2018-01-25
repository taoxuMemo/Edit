#include "cdbstjc.h"

CDBSTJC::CDBSTJC(QObject *parent) : CJCBase(parent)
{

}
bool CDBSTJC::NetInterFace(char *pData, int nLen, int nID)
{
    m_nNetID=nID;
    bool  bTag=this->CheckData(pData,nLen);
    if(bTag==false)
        return false;
    return true;
}
bool CDBSTJC::SerialInterFace(char *pData, int nLen, int nID)
{
    //解析数据
    char *couData=pData;
    int nLag=0;
    int nValLen;
    QString sCoding,sType,sValue;
    char *pcouData=couData;
    for(int i=0;i<nValLen;i++)
    {
        if(*pcouData=='-')
        {
            *pcouData=0;
            sCoding=QString(QLatin1String(couData));
            pcouData++;
            couData==pcouData;
            continue;
        }else if(*pcouData=='=')
        {
            *pcouData=0;
            sType=QString(QLatin1String(couData));
            pcouData++;
            couData==pcouData;
            continue;
        }else if(*pcouData==',')
        {
            *pcouData=0;
            sValue=QString(QLatin1String(couData));
            pcouData++;
            couData==pcouData;

            continue;
        }

    }

    return true;
}
