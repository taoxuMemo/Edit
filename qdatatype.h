#ifndef QDATATYPE_H
#define QDATATYPE_H

static const char * g_pCom[]={"com1","com2","com3","com4","com5","com6","com7","com8"};
static const char * g_pChn[]={"chn1","chn2","chn3","chn4","chn5","chn6","chn7","chn8"};
static const int    g_nBaud[]={115200,76800,57600,43000,38400,19200,14400,9600,4800,2400};
static const char   g_cData[]={8,7,6,5};
static const float  g_fStop[]={1,1.5,2};
static const char   g_cParity[]={'n','e','o'};

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
    char strJCX[20];  //监测项
    char strXY[20];  //协议
};
class QDatatype
{
public:
    QDatatype();
};

#endif // QDATATYPE_H
