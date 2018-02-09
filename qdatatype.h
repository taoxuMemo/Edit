#ifndef QDATATYPE_H
#define QDATATYPE_H

//**********************************211xieyi****************************
#define PACKAGEHEAD     2
#define DATALENGTH      4
#define CRCLENGTH       4
#define PACKAGETAIL     2
#define PACKAGEHEADTAIL PACKAGEHEAD+DATALENGTH+CRCLENGTH+PACKAGETAIL
//数据段结构组成表 字节长度
#define SJDJGZCB_QQBM_LEN                   20                          //请求编码 QN
#define SJDJGZCB_STBM_LEN                   5                           //系统编码 ST
#define SJDJGZCB_MLBM_LEN                   7                           //命令编码 CN
#define SJDJGZCB_FWMM_LEN                   9                           //访问密码
#define SJDJGZCB_SBWYBS_LEN                 27                          //设备唯一标识 MN
#define SJDJGZCB_CFBJYDBZ_LEN               6                           //拆分包及应答标志
#define SJDJGZCB_BZS_LEN                    9                           //总包数 PNUM
#define SJDJGZCB_BH_LEN                     8                           //包号 PNO
//系统编码表   编码
#define XTBMB_DBSZLJC_NO                    21                          //地表水质量监测
#define XTBMB_KQZLJC_NO                     22                          //空气质量监测
#define XTBMB_SHJZLJC_NO                    23                          //声环境质量监测
#define XTBMB_DXSZLJC_NO                    24                          //地下水质量监测
#define XTBMB_TRZLJC_NO                     25                          //土壤质量监测
#define XTBMB_HSZLJC_NO                     26                          //海水质量监测
#define XTBMB_HFXYJWJC_NO                   27                          //挥发性有机物监测
#define XTBMB_DQHJWRY_NO                    31                          //大气环境污染源
#define XTBMB_DBSTHJWRY_NO                  32                          //地表水体环境污染源
#define XTBMB_DXSTHJWRY_NO                  33                          //地下水体环境污染源
#define XTBMB_HYHJWRY_NO                    34                          //海洋环境污染源
#define XTBMB_TRHJWRY_NO                    35                          //土壤环境污染源
#define XTBMB_SHJWRY_NO                     36                          //声环境污染源
#define XTBMB_ZDHJWRY_NO                    37                          //振动环境污染源
#define XTBMB_FSXHJWRY_NO                   38                          //放射性环境污染源
#define XTBMB_GDYCWRY_NO                    39                          //工地扬尘污染源
#define XTBMB_DCHJWRY_NO                    41                          //电磁环境污染源
#define XTBMB_YQPFGCJK_NO                   51                          //烟气排放过程监控
#define XTBMB_WSPFGCJK_NO                   52                          //污水排放过程监控
#define XTBMB_XTJH_NO                       91                          //系统交互

//命令编码表 请求命令
#define MLBMB_SZCSSJJCFCS_QQML              1000                        //设置超时时间及重发次数
#define MLBMB_TQXCJSJ_QQML                  1011                        //提取现场机时间
#define MLBMB_SZXCJSJ_QQML                  1012                        //设置现场机时间
#define MLBMB_TQSSSJJG_QQML                 1061                        //提取实时数据间隔
#define MLBMB_SZSSSJJG_QQML                 1062                        //设置实时数据间隔
#define MLBMB_TQFZSJJG_QQML                 1063                        //提取分钟数据间隔
#define MLBMB_SZFZSJJG_QQML                 1064                        //设置分钟数据间隔
#define MLBMB_SZXCJMM_QQML                  1072                        //设置现场机密码
#define MLBMB_QWRWSSSJ_QQML                 2011                        //取污染物实时数据
#define MLBMB_QSBYXZTSJ_QQML                2021                        //取设备运行状态数据
#define MLBMB_QWRWRLSSJ_QQML                2031                        //取污染物日历史数据
#define MLBMB_QSBYSSJRLSSJ_QQML             2041                        //取设备运行时间日历史数据
#define MLBMB_QWRWFZSJ_QQML                 2051                        //取污染物分钟数据
#define MLBMB_QWRWXSSJ_QQML                 2061                        //取污染物小时数据
#define MLBMB_LDJZLCJZ_QQML                 3011                        //零点校准量程校准
#define MLBMB_JSCY_QQML                     3012                        //即时采样
#define MLBMB_QDQXFC_QQML                   3013                        //启动清洗/反吹
#define MLBMB_BDCY_QQML                     3014                        //比对采样
#define MLBMB_CBLY_QQML                     3015                        //超标留样
#define MLBMB_SZCYSJZQ_QQML                 3016                        //设置采样时间周期
#define MLBMB_TQCYSJZQ_QQML                 3017                        //提取采样时间周期
#define MLBMB_TQCYSJ_QQML                   3018                        //提取出样时间
#define MLBMB_TQSBWYBS_QQML                 3019                        //提取设备唯一标识
#define MLBMB_TQXCJXX_QQML                  3020                        //提取现场机信息
#define MLBMB_SZXCJCS_QQML                  3021                        //设置现场机参数


//命令编码 上传命令
#define MLBMB_SCXCJSJ_SCML                  1011                        //上传现场机时间
#define MLBMB_SCSSSJJG_SCML                 1061                        //上传实时数据间隔
#define MLBMB_SCFZSJJG_SCML                 1063                        //上传分钟数据间隔
#define MLBMB_SCWRWSSSJ_SCML                2011                        //上传污染物实时数据
#define MLBMB_SCSBYXZTSJ_SCML               2021                        //上传设备运行状态数据
#define MLBMB_SCWRWRLSSJ_SCML               2031                        //上传污染物日历史数据
#define MLBMB_SCSBYXSJRLSSJ_SCML            2041                        //上传设备运行时间日历史数据
#define MLBMB_SCWRWFZSJ_SCML                2051                        //上传污染物分钟数据
#define MLBMB_SCWRWXSSJ_SCML                2061                        //上传污染物小时数据
#define MLBMB_SCSCYKJSJ_SCML                2081                        //上传数采仪开机时间
#define MLBMB_SCCBLYXX_SCML                 3015                        //上传超标留样信息
#define MLBMB_SCCYSJZQ_SCML                 3017                        //上传采样时间周期
#define MLBMB_SCCYSJ_SCML                   3018                        //上传出样时间
#define MLBMB_SCSBWYBS_SCML                 3019                        //上传设备唯一标识
#define MLBMB_SCXCJXX_SCML                  3020                        //上传现场机信息

//命令编码 通知信息
#define MLBMB_XCJSJJZQQ_TZML                1013                        //现场机时间校准请求
#define MLBMB_TZCKWRWSSSJ_TZML              2012                        //停止察看污染物实时数据
#define MLBMB_TZCKSBYXZT_TZML               2022                        //停止察看设备运行状态

//命令编码 交互命令
#define MLBMB_QQYD_JHML                     9011                        //用于现场机回应接收的上位机请求命令是否有效
#define MLBMB_ZXJG_JHML                     9012                        //用于现场机回应接收的上位机请求命令执行结果
#define MLBMB_TZYD_JHML                     9013                        //回应通知命令
#define MLBMB_SJYD_JHML                     9014                        //数据应答命令

//水监测因子编码表
#define SJCYZ_WS_BM                         w00000                      //污水
#define SJCYZ_PHZ_BM                        w01001                      //pH 值
#define SJCYZ_HXXYL_BM                      w01018                      //化学需氧量
#define SJCYZ_AD_BM                         w21003                      //氨氮
//气监测因子编码表
#define QJCYZ_FQ_BM                         a00000                      //废气
#define QJCYZ_YQLS_BM                       a01011                      //烟气流速
#define QJCYZ_YQWD_BM                       a01012                      //烟气温度
#define QJCYZ_YQYL_BM                       a01013                      //烟气压力
#define QJCYZ_YQSD_BM                       a01014                      //烟气湿度
#define QJCYZ_YDJMJ_BM                      a01016                      //烟道截面积
#define QJCYZ_YQHL_BM                       a19001                      //氧气含量
#define QJCYZ_DYHW_BM                       a21002                      //氮氧化物
#define QJCYZ_EYHL_BM                       a21026                      //二氧化硫
#define QJCYZ_YC_BM                         a34013                      //烟尘

//**********************************************************************************
#define ITEMSTULEN                         12                           //监测项长度


extern  char g_DeviceMark[SJDJGZCB_SBWYBS_LEN+1];//最后一位结束位

extern const char * g_pCom[];//={"com1","com2","com3","com4","com5","com6","com7","com8"};
extern const char * g_pChn[];//={"chn1","chn2","chn3","chn4","chn5","chn6","chn7","chn8"};
extern const char * g_pSJCYZNOCOU[];
static const int    g_nBaud[]={115200,76800,57600,43000,38400,19200,14400,9600,4800,2400};
static const char   g_cData[]={8,7,6,5};
static const float  g_fStop[]={1,1.5,2};
static const char   g_cParity[]={'n','e','o'};
extern const char * g_ipaddr[];//={"IP1","IP2","IP3","IP4","IP5","IP6"};

struct  stuChannel{
    bool isrun;
    char nID;
    int  nBaud;
    char nData;
    float nStop;
    char nParity;
    char *pName;
    char *pModel;
    char *pType;
    bool bMinAvg;
    bool bMinMax;
    bool bMinMin;
    bool bMinTotal;
    bool bHourAvg;
    bool bHourMax;
    bool bHourMin;
    bool bHourTotal;
    bool bDayAvg;
    bool bDayMax;
    bool bDayMin;
    bool bDayTotal;
    int nAlarmUp;
    int nAlarmDown;
    int nCycle;
    char strCS[50];  //厂商
    char strXH[20];  //型号
    char strJCX[7];  //监测项  如污水是w00000
    char strXY[20];  //协议
};
struct stuIPAddr{
    bool isChange;
    bool bIsrun;
    char sName[50];
    char sIP[20];
    int nPort;
    char sExtend[20];

};
//水监测因子
struct stuSJCYZ
{
    char sValue[15];
    char sTime[15];
//    SJCYZ()
//    {
//        for(int i=0;i<15;i++)
//            sValue[i]=0,sTime[i]=0;
//    }
};
//因子上报设置
struct stuYZSBSZ
{
    char sCoding[7];                //编码
    double  dAlarmUp;               //报警上限
    double  dAlarmDown;             //报警下限
    bool rtd;
    bool fcou;
    bool fmax;
    bool fmin;
    bool favg;

    bool hcou;
    bool hmax;
    bool hmin;
    bool havg;

    bool rcou;
    bool rmax;
    bool rmin;
    bool ravg;
};

//水监测因子编码表
struct stuSJCYZBMB
{
    char sCoding[7];        //编码
    char sName[20];         //中文名称
    char sOldCoding[4];     //源编码
    char sNDUnit[20];       //计量单位（浓度）
    char sPFLUint[10];      //计量单位（排放量）
    char sDataLen[10];      //数据长度（浓度）
    int  nOper;             //操作符
    int  nCoef;             //系数
    stuYZSBSZ stuYZ;
};


class QDatatype
{
public:
    QDatatype();
};

#endif // QDATATYPE_H
