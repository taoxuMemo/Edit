#ifndef CJCBASE_H
#define CJCBASE_H

#include <QObject>
#include "qdatatype.h"
#include "ctool.h"
#include "cprotocol.h"
#include "qlist.h"
#include "qqueue.h"
class CJCBase : public CProtocol
{
    Q_OBJECT
public:
    explicit CJCBase(QObject *parent = nullptr);
    bool    virtual SerialInterFace(char *pData,int nLen,int nID)=0;//串口接口  参数1.内容2.长度3.接口号
    bool    virtual NetInterFace(char *pData,int nLen,int nID)=0;   //网络接口  参数1.内容2.长度3.接口号
    char  m_sQQBM[SJDJGZCB_QQBM_LEN+1];//请求编码
    char  m_sXTBM[SJDJGZCB_STBM_LEN+1]; //系统编码
    char  m_sMLBM[SJDJGZCB_MLBM_LEN+1]; //命令编码
    char  m_sFWMM[SJDJGZCB_FWMM_LEN+1]; //访问密码
    char  m_sSBWYBS[SJDJGZCB_SBWYBS_LEN+1];//设备唯一标识
    int   m_nXTBM;
    char  m_nMark;           //分包及应答标志
    int   m_nPNUM;           //分包数量
    int   m_nPNO;            //分包号
    //**********************************************************
    //   int
    //*********************常规参数变量***********************
    QList<stuSJCYZBMB> m_listJCYZ;      //存储测量的监测因子编码表
    QQueue<QString>    m_queCJSJ;       //存储从地板采集的数据
    stuSJCYZBMB m_stuSJCYZBMB[20];      //选中的上报编码表中的因子
    stuYZSBSZ   m_stuYZSBSZ[20];        //对选中的因子上报设置
    int m_nMSBJG,m_nFSBJG;  //1.上报间隔秒   2.上报间隔分钟
    bool m_bSSSJ;   //实时数据上报
    bool m_bFZSJ;   //分钟数据上报
    bool m_bXSSJ;   //小时数据上报
    bool m_bRSJ;    //日数据上报
    bool m_bKGL;    //开关量
    int   m_nOverTime;       //超时响应时间
    int   m_nReCount;        //重发次数
    bool  CheckData(char * pData, int nLen);
    bool  CommandData();
    bool  Splitinst(char *p,QString &a,QString &b);  //拆分指令等号前后的
    //***********拼接字符串********
   // double CalcCou(double );
    QString SpellUpStr(stuSJCYZBMB stu,double dRtd);
  //  QString SpellUpStr(stuSJCYZBMB stu,int type,double dMax,double dMin,double dAvg); //type 判断分钟还是小时还是日
 //   QString SpellUpStr(stuSJCYZBMB stu,int type,double dMax,double dMin,double dAvg,double dTotal);
    QString SpellUpStr(stuSJCYZBMB stu,int type,double dMax,double dMin,double dAvg,double dTotal=0,double dStand=0); //type 判断分钟还是小时还是日
    QString SpellUpStr(stuSJCYZBMB stu,int type,double dMax,double dMin,double dAvg,double dTotal,double dMaxZS,double dMinZS,double dAvgZS,double dTotalZS);//type 判断分钟还是小时还是日
    QString SpellUpDataTable(QString QQBM,QString MLBM,int nFlag,QString sDataArea);    //拼接数据段结构组成表



private:

    bool    virtual UploadReal();  //上传实时数据

signals:

public slots:
};

#endif // CJCBASE_H
