#ifndef CJCBASE_H
#define CJCBASE_H

#include <QObject>
#include "qdatatype.h"
#include "ctool.h"
class CJCBase : public QObject
{
    Q_OBJECT
public:
    explicit CJCBase(QObject *parent = nullptr);
    char  m_sQQBM[SJDJGZCB_QQBM_LEN+1];
    char  m_sXTBM[SJDJGZCB_STBM_LEN+1];
    char  m_sMLBM[SJDJGZCB_MLBM_LEN+1];
    char  m_sFWMM[SJDJGZCB_FWMM_LEN+1];
    char  m_nMark;           //分包及应答标志
    int   m_nPNUM;           //分包数量
    int   m_nPNO;            //分包号

    int   m_nOverTime;       //超时响应时间
    int   m_nReCount;        //重发次数
    bool  CheckData(char * pData, int nLen);
    bool  CommandData();
signals:

public slots:
};

#endif // CJCBASE_H
