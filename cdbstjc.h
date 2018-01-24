#ifndef CDBSTJC_H
#define CDBSTJC_H
#include"QObject"
#include "cjcbase.h"
#include "qdatatype.h"
//#include"cprotocol.h"
class CDBSTJC : public CJCBase
{
    Q_OBJECT
public:
    explicit CDBSTJC(QObject *parent = nullptr);
    bool setData();
    bool NetInterFace(char *pData,int nLen,int nID);
    bool SerialInterFace(char *pData,int nLen,int nID);
    stuSJCYZ m_stuWS,m_stuPHZ,m_stuHXXYL,m_stuAD;//污水，ph值，化学需氧量，氨氮
    char    m_sWS[9];       //污水
    char    m_sPHZ[6];      //PH值
    char    m_sHXXYL[8];    //化学需氧量
    char    m_sAD[8];       //氨氮
signals:

public slots:
};

#endif // CDBSTJC_H
