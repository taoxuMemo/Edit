#include "cdbstjc.h"
#include"coperationconfig.h"
#include "cmysqlite.h"
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
//参数：*pData指向数据段指针，nLen数据段结构长度
bool CDBSTJC::SerialInterFace(char *pData, int nLen, int nID)
{
    if(CheckData(pData,nLen)!=true)
    {
        COperationConfig::writelog(ERRLOGXYJXSJDYC);
        return false;
    }
    int nSJDJG=SJDJGZCB_QQBM_LEN+1+SJDJGZCB_STBM_LEN+1+SJDJGZCB_MLBM_LEN+1+SJDJGZCB_FWMM_LEN+1+SJDJGZCB_SBWYBS_LEN+1+SJDJGZCB_CFBJYDBZ_LEN+1;

    //解析数据
    char *couData=(pData+=nSJDJG);  //指向指令参数cp=
    if(strncmp(couData,"CP=&&",5)!=0)
     {
        COperationConfig::writelog(ERRLOGXYJXSJDCP);
        return false;
    }
    couData+=5;                         //couData指向数据区

    //int nLag=nLen-nSJDJG-5;
    int nValLen=nLen-nSJDJG-5;          //nValLen数据区长度
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
            //存入数据库


            sCoding=NULL;
            sType=NULL;
            sValue=NULL;
            continue;
        }

    }

    return true;
}
