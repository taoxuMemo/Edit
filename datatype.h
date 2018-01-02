#ifndef DATATYPE_H
#define DATATYPE_H

const char * g_pCom[]={"com1","com2","com3","com4","com5","com6","com7","com8"};
const char * g_pChn[]={"chn1","chn2","chn3","chn4","chn5","chn6","chn7","chn8"};
const int    g_nBaud[]={115200,76800,57600,43000,38400,19200,14400,9600,4800,2400};
const char   g_cData[]={8,7,6,5};
const float  g_fStop[]={1,1.5,2};
const char   g_cParity[]={'n','e','o'};

struct  stuChannel{
    char nID;
    char nBaud;
    char nData;
    char nStop;
    char nParity;
    char *pName;
    char *pModel;
    char *pType;
};
#endif // DATATYPE_H
