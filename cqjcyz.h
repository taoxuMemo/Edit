#ifndef CQJCYZ_H
#define CQJCYZ_H

#include <QObject>
#include "cqjcyz.h"
#include "cjcbase.h"
class CQJCYZ : public CJCBase
{
    Q_OBJECT
public:
    explicit CQJCYZ(QObject *parent = nullptr);
    ~CDBSTJC();
    double m_dTS,m_dBA,m_dPS,m_dXSW,m_dQSH;//烟气温度 环境大气压值  烟气静压值 烟气绝对湿度
    double m_nPresDuff;                       //气压差值
    bool SerialInterFaceNew(char *pData,int nLen,int nID);
    bool NetInterFace(char *pData, int nLen, int nID);
    void timerEvent(QTimerEvent *event);
    bool GetValue(int nType);
    double zsValue(double dZS);
    int m_nTimerId;
signals:

public slots:
};

#endif // CQJCYZ_H
