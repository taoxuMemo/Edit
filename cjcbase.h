#ifndef CJCBASE_H
#define CJCBASE_H

#include <QObject>
#include "qdatatype.h"
#include "ctool.h"
#include "cprotocol.h"
class CJCBase : public CProtocol
{
    Q_OBJECT
public:
    explicit CJCBase(QObject *parent = nullptr);
    char  m_sQQBM[SJDJGZCB_QQBM_LEN+1]; //请求编码
    char  m_sXTBM[SJDJGZCB_STBM_LEN+1]; //系统编码
    char  m_sMLBM[SJDJGZCB_MLBM_LEN+1]; //命令编码
    char  m_sFWMM[SJDJGZCB_FWMM_LEN+1]; //访问密码
    char  m_nMark;           //分包及应答标志
    int   m_nPNUM;           //分包数量
    int   m_nPNO;            //分包号
//*********************常规参数变量***********************
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
private:
    bool    virtual SerialInterFace(char *pData,int nLen,int nID)=0;//串口接口  参数1.内容2.长度3.接口号
    bool    virtual NetInterFace(char *pData,int nLen,int nID)=0;   //网络接口  参数1.内容2.长度3.接口号

signals:

public slots:
};

#endif // CJCBASE_H
