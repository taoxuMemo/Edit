#ifndef CPROTOCOL_H
#define CPROTOCOL_H

#include <QObject>
#include"cdbstjc.h"

class CProtocol : public QObject
{
    Q_OBJECT
public:
    explicit CProtocol(QObject *parent = nullptr);
    bool PackageCheck(char * pData,int nLen);  //验证包是否有效，并且赋值给成员变量
    int  AddPackageCheck(char *pData,int nLen);//封装包
    char m_sData[1500];
    //***************污染源类型******************
    CDBSTJC m_dbstjc;
signals:

public slots:
};

#endif // CPROTOCOL_H
