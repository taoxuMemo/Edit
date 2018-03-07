#ifndef CCOLSVR_H
#define CCOLSVR_H
#include <string.h>
#include <qlist.h>
struct stuCol
{
    stuCol()
    {
        memset(sName,0,7);
        memset(sType,0,7);
        dvalue=0.0;
    }
    char sName[7];
    char sType[7];
    double dvalue;
};

class CColSvr
{
public:
    CColSvr();
    bool    setData(char *pData ,int nLen);
    int     m_nST,m_nCN;        //  ST CN的编码
    char    m_sData[2048];     //不包含&&数据区内容
    int     m_nArea;           //不包含&&数据区长度
    int     m_nErrCode;         //错误码
    QList<stuCol>   getlist();
};

#endif // CCOLSVR_H
