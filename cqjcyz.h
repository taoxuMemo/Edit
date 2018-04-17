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
    ~CQJCYZ();
    double m_dTS,m_dBA,m_dPS,m_dXSW,m_dQSH;//烟气温度 环境大气压值  烟气静压值 烟气绝对湿度
    double m_nPresDuff;                       //气压差值
    bool SerialInterFace(char *pData,int nLen,int nID);//串口接口  参数1.内容2.长度3.接口号
    bool SerialInterFaceNew(char *pData,int nLen,int nID);
    bool NetInterFace(char *pData, int nLen, int nID);
    void timerEvent(QTimerEvent *event);
    bool GetValue(int nType);
    bool GetMinValue();//得到分钟数据
    bool GetHourValue();//得到小时数据
    bool GetHDayValue();//得到天数据
    bool GetVal(QString strCoding,double dMax,double dMin,double dAvg,double dCou,double dzsMax,double dzsMin,double dzsAvg);      //得到最大最小平均数据
    double zsValue(double dZS);
    int m_nTimerId;
signals:

public slots:
};

#endif // CQJCYZ_H
