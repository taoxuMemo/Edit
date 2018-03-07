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
    ~CDBSTJC();
    bool init();
    void timerEvent( QTimerEvent *event );
    bool setData();
    bool NetInterFace(char *pData,int nLen,int nID);
    bool SerialInterFace(char *pData,int nLen,int nID);
    bool SerialInterFaceNew(char *pData,int nLen,int nID);
    bool GetValue(int nType);//取数据库中的数据 参数nType 1 分钟 2 小时 3 天
    QString SpellStr(QString coding,int type ,double dMax,double dMin,double dAvg,double dTotal);//拼写type 1分钟 2 小时 3 天
    stuSJCYZ m_stuWS,m_stuPHZ,m_stuHXXYL,m_stuAD;//污水，ph值，化学需氧量，氨氮
    char    m_sWS[9];       //污水
    char    m_sPHZ[6];      //PH值
    char    m_sHXXYL[8];    //化学需氧量
    char    m_sAD[8];       //氨氮
    stuSJCYZBMB m_stuUpType;
    int m_nTimerId;//定时器标志
signals:

public slots:
};

#endif // CDBSTJC_H
