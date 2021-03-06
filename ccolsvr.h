#ifndef CCOLSVR_H
#define CCOLSVR_H
#include <string.h>
#include <qlist.h>
#include "qbytearray.h"
#include "qdatatype.h"

class CColSvr
{
public:
    CColSvr();
    bool    setData(char *pData ,int nLen);
    int     m_nST,m_nCN;        //  ST CN的编码
    char    m_sData[2048];     //不包含&&数据区内容
    int     m_nArea;           //不包含&&数据区长度
    int     m_nErrCode;         //错误码
    QString m_strSetting;       //拼凑下发字符串
    bool GetSZLStr(int nPort, bool bMark, QString sCoding,QString sPol);        //得到数字量字符串
    bool GetMNLStr(int nPort, bool bMark,int nType);        //得到模拟量字符串
    bool GetKGLStr(int nPort,int nType);        //得到开关量字符串
    QByteArray GetSendStr();
    QList<stuCol>   getlist();
    QList<stuInfo>  getlistinfo();

};

#endif // CCOLSVR_H
