#ifndef COPERATIONCONFIG_H
#define COPERATIONCONFIG_H

#include "qdatatype.h"
#include "QFile"
#include"QSettings"
#define    CONFIGOPENERR      0x00000001  //配置文件打开失败
#define    CONFIGCOMLEN       0x00000002  //配置文件com长度错误
#define    CONFIGCOMVOER      0x00000003  //配置文件com对应的通道号不是1--8
#define    CONFIGISRUN        0x00000004   // 配置文件通道isrun错误
#define    CONFIGBUAD         0x00000005   //配置文件提取波特率错误
#define    CONFIGDATA         0x00000006   //配置文件提取数据位错误
#define    CONFIGSTOP         0x00000007   //配置文件提取停止位错误
#define    CONFIGPARITY       0x00000008   //配置文件提取校验位错误
class COperationConfig
{
public:
    COperationConfig();
    ~COperationConfig();
    bool m_bTag;                   //判断配置文件是否存在
    int  ReadCom(int num);         //读取串口号参数代表串口号，返回对应的通道号，不含号码前的字母。
    bool ReadChn(stuChannel * stu,int num);   //读取通道号参数代表通道号，返回通道结构
    bool WriteCom(int num);        //写入串口对应的通道号
    bool writeChn(stuChannel chn); //写入通道参数
    static   void writelog(int nErr,char * sRemark=NULL);//参数nErr错误码 sremark备注
private:
    const char * m_scom="com";
    const char * m_schn="chn";
    const char * m_sFileName="./config.ini";//配置文件名
    const char * m_sLogName="./log";   //日志文件名后边加日期
    QSettings * m_file;           //
};

#endif // COPERATIONCONFIG_H
