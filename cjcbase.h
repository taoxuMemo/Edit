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
    bool    virtual SerialInterFaceNew(char *pData,int nLen,int nID)=0;
    bool    virtual init();
    bool    getItem();
    bool    TcpSendVal(char *pData,int nLen,int nID=-1);            //nID表示上传SOCKET号 默认-1全部上传
    bool    SendComSet();
    char    m_sQQBM[SJDJGZCB_QQBM_LEN+1];//请求编码
    char    m_sXTBM[SJDJGZCB_STBM_LEN+1]; //系统编码
    char    m_sMLBM[SJDJGZCB_MLBM_LEN+1]; //命令编码
    char    m_sFWMM[SJDJGZCB_FWMM_LEN+1]; //访问密码
    char    m_sSBWYBS[SJDJGZCB_SBWYBS_LEN+1]; //设备唯一标识
    char    m_sDataArea[2048];                //数据区内容
    int     m_nDataArea;                      //数据区长度
//    int   m_nXTBM;
    char  m_nMark;           //分包及应答标志
    int   m_nPNUM;           //分包数量
    int   m_nPNO;            //分包号
   // int   m_nIPNO;           //当前数据的IP地址
    //**********************************************************
    //   int
    //*********************常规参数变量***********************
    QList<stuSJCYZBMB> m_listJCYZ;      //存储测量的监测因子编码表
    QQueue<QString>    m_queCJSJ;       //存储从地板采集的数据
    stuSJCYZBMB m_stuSJCYZBMB[ITEMSTULEN];      //选中的上报编码表中的因子
    stuYZSBSZ   m_stuYZSBSZ[ITEMSTULEN];        //对选中的因子上报设置
    int m_nMSBJG,m_nFSBJG;  //1.上报间隔秒   2.上报间隔分钟
    bool m_bSSSJ;   //实时数据上报
    bool m_bFZSJ;   //分钟数据上报
    bool m_bXSSJ;   //小时数据上报
    bool m_bRSJ;    //日数据上报
    bool m_bKGL;    //开关量
    int   m_nOverTime;       //超时响应时间
    int   m_nReCount;        //重发次数
    QList<UpDataStu> m_listSend;
    bool    SendData();  //从发送队列里提取发送
    bool    AnsData();   //接收到平台相应从列表里删除
    bool  CheckData(char * pData, int nLen);
    bool  CommandData();
    bool  Splitinst(char *p,QString &a,QString &b);  //拆分指令等号前后的
    QList<QString>  SplitMH(char *pd , int nlen);    //拆分数据CP=后数据段数量 以冒号为分割

   // QString getSplit();
    //*************************************与平台通讯数据解析********************************************
    int         GetCN(char * pData,int nLen);//得到命令编码
    QString     GetQN(char * pData,int nLen);//得到请求编码
    int         GetST(char * pData,int nLen);//得到系统编码
    QString     GetPW(char * pData,int nLen);//得到访问密码
    QString     GetMN(char * pData,int nLen);//得到设备唯一标识
    bool        CommandCode(int nCommand);//解析上位机传过来的命令编码
    bool        Ans1000();//设置超时时间及重发次数 参数为CP=后边内容
    bool        Ans1011(); //提取现场机时间 参数为CP=后边内容
    bool        Ans1012(); //提取现场机时间 参数为CP=后边内容
    bool        Ans1061(); //提取现场机时间 参数为CP=后边内容
    bool        Ans1062(); //提取现场机时间 参数为CP=后边内容
    bool        Ans1063(); //提取现场机时间 参数为CP=后边内容
    bool        Ans1064(); //提取现场机时间 参数为CP=后边内容
    bool        Ans1072(); //设置现场机访问密码
    bool        Ans2011(); //取污染物实时数据
    bool        Ans9014(); //上位机应答数据
    //***********拼接字符串********
    // double CalcCou(double );
    QString SpellUpStr(stuSJCYZBMB stu,double dRtd);
    //  QString SpellUpStr(stuSJCYZBMB stu,int type,double dMax,double dMin,double dAvg); //type 判断分钟还是小时还是日
    //   QString SpellUpStr(stuSJCYZBMB stu,int type,double dMax,double dMin,double dAvg,double dTotal);
    QString SpellUpStr(stuSJCYZBMB stu,int type,double dMax,double dMin,double dAvg,double dTotal=0,double dStand=0); //type 判断分钟还是小时还是日
    QString SpellUpStr(stuSJCYZBMB stu,int type,double dMax,double dMin,double dAvg,double dTotal,double dMaxZS,double dMinZS,double dAvgZS);//type 判断分钟还是小时还是日
    QString SpellUpDataTable(QString QQBM,QString MLBM,int nFlag,QString sDataArea);    //拼接数据段结构组成表
    bool    virtual UploadReal();  //上传实时数据
   //************************得到数据段各个字段的值**********************
 //   bool getQQBMQN(QString&,char *);
    bool AiToCoding(stuCol&);  //计算模拟量实际值，返回0错误 1正常

private:



signals:

public slots:
};

#endif // CJCBASE_H
