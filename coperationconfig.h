#ifndef COPERATIONCONFIG_H
#define COPERATIONCONFIG_H

#include "qdatatype.h"
#include "QFile"
#include"QSettings"
#define    CONFIGOPENERR            0x00000001      //配置文件打开失败
#define    CONFIGCOMLEN             0x00000002      //配置文件com长度错误
#define    CONFIGCOMVOER            0x00000003      //配置文件com对应的通道号不是1--8
#define    CONFIGISRUN              0x00000004      //配置文件通道isrun错误
#define    CONFIGBUAD               0x00000005      //配置文件提取波特率错误
#define    CONFIGDATA               0x00000006      //配置文件提取数据位错误
#define    CONFIGSTOP               0x00000007      //配置文件提取停止位错误
#define    CONFIGPARITY             0x00000008      //配置文件提取校验位错误
#define    CONFIGCHNMINAVG          0x00000009      //配置文件提取favg错误
#define    CONFIGCHNMINMAX          0x0000000A      //配置文件提取fmin错误
#define    CONFIGCHNMINMIN          0x0000000B      //配置文件提取fmax错误
#define    CONFIGCHNMINTOTAL        0x0000000C      //配置文件提取ftotal错误
#define    CONFIGCHNHOURAVG         0x0000000D      //配置文件提取 xavg错误
#define    CONFIGCHNHOURMAX         0x0000000E      //配置文件提取 xmin错误
#define    CONFIGCHNHOURMIN         0x0000000F      //配置文件提取 xmax错误
#define    CONFIGCHNHOURTOTAL       0x00000011      //配置文件提取 xtotal错误
#define    CONFIGCHNDAYAVG          0x00000012      //配置文件提取 ravg错误
#define    CONFIGCHNDAYMAX          0x00000013      //配置文件提取 rmin错误
#define    CONFIGCHNDAYMIN          0x00000014      //配置文件提取 rmax错误
#define    CONFIGCHNDAYTOTAL        0x00000015      //配置文件提取 rtotal错误
#define    CONFIGIPNAMELEN          0x00000016      //配置文件提取 IP地址中的name长度错误
#define    CONFIGIPEXTENDLEN        0x00000017      //配置文件提取 IP地址中的extend长度错误
#define    CONFIGIPIPADDRLEN        0x00000018      //配置文件提取 IP地址中的IP长度错误

//*********************************数据库错误****************************************8
#define    ERRLOGDBOPENFAIL         0x00000040      //数据库打开失败
#define    ERRLOGDBINSERTRD         0x00000041      //数据库打开失败
#define    ERRLOGDBSELTIME          0x00000042      //查询实时数据起始时间与终止时间错误
#define    ERRLOGDBSELEXEC          0x00000043      //执行select sql语句时异常
//***********************************协议解析异常******************************************
#define    ERRLOGXYJXSJDYC         0x00000081       //数据段结构异常
#define    ERRLOGXYJXSJDCP         0x00000082       //数据段结构CP=错误

//************************************数据处理错误********************************************
#define    ERRLOGTIMETYPE         0x00000060       //数据段结构CP=错误

class COperationConfig
{
public:
    COperationConfig();
    ~COperationConfig();
    bool m_bTag;                   //判断配置文件是否存在
    int  ReadCom(int num);         //读取串口号参数代表串口号，返回对应的通道号，不含号码前的字母。
    bool ReadChn(stuChannel * stu,int num);   //读取通道号参数代表通道号，返回通道结构
    bool WriteCom(int nCom,int nChn);        //写入串口对应的通道号
    bool writeChn(stuChannel chn,int num); //写入通道参数
    static   void writelog(int nErr,char * sRemark=NULL);//参数nErr错误码 sremark备注
    bool CheckBool(QString str); //判断传进来str是不是bool类型

    bool ReadIPAddr(stuIPAddr *stu,int num);//读取IP地址
    bool WriteIPAddr(stuIPAddr stu,int num); //写入IP地址
private:
    const char * m_scom="com";
    const char * m_schn="chn";
    const char * m_sFileName="./config.ini";//配置文件名
    const char * m_sLogName="./log";   //日志文件名后边加日期
    QSettings * m_file;           //
};

#endif // COPERATIONCONFIG_H
