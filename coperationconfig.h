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
#define    CONFIGPASSWORD           0x00000019      //配置文件中的访问密码错误
#define    CONFIGEQUIPMENTID        0x0000001A      //配置文件中的设备唯一标识错误
#define    CONFIGCOLERROR           0x0000001B      //读取配置文件COL有字段不存在
#define    CONFIGCODINGERROR        0x0000001C      //读取item段的coding错误
#define    CONFIGTYPEERROR          0x0000001D      //读取col段的TYPE错误错误
#define    CONFIGCOMERROT           0x0000001E      //读取串口配置信息错误
#define    CONFIGPROTOCOLERR        0x00000020      //配置文件提取协议错误
#define    CONFIGGETAICODING        0x00000020      //配置文件提取AI通道Coding

//*************************************xitongcuowu*********************************************
#define    SYSSTARTCONSERIALERROR   0x000000B1      //qidongwufadakaichuankou
//*********************************数据库错误****************************************8
#define    ERRLOGDBOPENFAIL         0x00000040      //数据库打开失败
#define    ERRLOGDBINSERTRD         0x00000041      //存储实时数据失败
#define    ERRLOGDBINSERTZSRD       0x00000046    //存储折算实时数据失败
#define    ERRLOGDBINSERTINFO       0x00000045      //存储信息数据失败
#define    ERRLOGDBSELTIME          0x00000042      //查询实时数据起始时间与终止时间错误
#define    ERRLOGDBSELEXEC          0x00000043      //执行select sql语句时异常
#define    ERRLOGDBDATALEN          0x00000044      //执行查询数据长度时语句时异常
#define    ERRLOGDBIPSTATUS         0x00000045      //存储IP连接状态
//***********************************协议解析异常******************************************
#define    ERRLOGXYJXSJDYC          0x00000081       //数据段结构异常
#define    ERRLOGXYJXSJDCP          0x00000082       //数据段结构CP=错误

#define   ERRORPACKAGEHEAD          0x00000091       //baotoucuowu
#define   ERRORPACKAGELEN           0x00000092       //baotoucuowu
#define   ERRORPACKAGECRC           0x00000093       //baotoucuowu
#define   ERRORPACKAGETAIL          0x00000094       //baotoucuowu
#define   ERRORPACKAGELENTYPE       0x00000095       //baotoucuowu
#define   ERRORPACKAGECRCTYPE       0x00000096       //baotoucuowu
#define   ERRORPACKAGEST            0x00000097       //
#define   ERRORSJDJGZCCNLEN         0x00000098       //数据段结构组成CN长度错误
#define   ERRORSJDJGZCCNNAME        0x00000099       //数据段结构组成CN长度错误
#define   ERRORSTERROR              0x000000A0       //系统交互ST码错误
#define   ERRORSERIALPROTOCOL       0x000000A1          //新串口解析协议
#define   ERROROPENCOM              0x000000A2      //打开串口失败
#define   ERRORPROAISET             0x000000A3          //模拟量转数字量错误
#define   ERRORPROAINUM             0x000000A4         //模拟量串口号错误
//************************************数据处理错误********************************************
#define    ERRLOGTIMETYPE           0x00000060       //数据段结构CP=错误
//***************************************网络连接错误****************************************
#define     ERRNETCREATESOCKET        0x00000101      //创建socket错误
#define     ERRNETCONNECTERROR        0x00000102      //连接错误
#define     ERRNETTIMEOUT             0x00000103      //连接超时
#define     ERRNETOTHERERROR          0x00000104      //其他错误
#define     ERRNETCREATECON           0x00000105      //connect错误

#define     ERRRECVSELECT             0x00000106        //select错误
#define     ERRRECVTIMEOUT            0x00000107       //接收超时

class COperationConfig
{
public:
    COperationConfig();
    ~COperationConfig();
    bool m_bTag;                   //判断配置文件是否存在
    int  ReadCom(int num);         //读取串口号参数代表串口号，返回对应的通道号，不含号码前的字母。
    bool ReadChn(stuChannel * stu,int num);     //读取通道号参数代表通道号，返回通道结构
    bool ReadAI(stuAIChan * stu, int num);      //读取模拟量通道配置
    bool WriteCom(int nCom,int nChn);        //写入串口对应的通道号
    bool writeChn(stuChannel chn,int num); //写入通道参数
    static   void writelog(int nErr,char * sRemark=NULL);//参数nErr错误码 sremark备注
    static   void writeRD(QString str);
    static   void writeSendRD(QString str);
    bool CheckBool(QString str); //判断传进来str是不是bool类型

//    bool ReadItem(stuYZSBSZ *stu,int num);//读取配置文件ITEM监测因子字段

    bool ReadIPAddr(stuIPAddr *stu,int num);//读取IP地址
    bool WriteIPAddr(stuIPAddr stu,int num); //写入IP地址
    bool ReadItem(stuYZSBSZ *stu,int num); //读取监测项的内容
    QString getText(QString ,QString );
    void    writeText(QString,QString,QString);   //顺序1group2key3alue
private:
    const char * m_scom="com";
    const char * m_schn="chn";
    const char * m_sFileName="./config.ini";//配置文件名
    const char * m_sLogName="./log";   //日志文件名后边加日期
    QSettings * m_file;           //
};

#endif // COPERATIONCONFIG_H
