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
    return true;
}
