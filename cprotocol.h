#ifndef CPROTOCOL_H
#define CPROTOCOL_H

#include <QObject>
//#include"cdbstjc.h"
//#include"mainwindow.h"
class MainWindow;
class CProtocol : public QObject
{
    Q_OBJECT
public:
    explicit CProtocol(QObject *parent = nullptr);
    int     PackageCheck(char * pData,int nLen);  //验证包是否有效，并且赋值给成员变量,返回包类型
    int     AddPackageCheck(char *pData,int nLen);//封装包
    QByteArray SpellPackage(QString);
    char    m_sData[2048];
    int     m_nDataLen;
    int     m_nSerID;
    int     m_nNetID;
    MainWindow * m_pMain;
protected:

private:
    bool    virtual SerialInterFace(char *pData,int nLen,int nID)=0;//串口接口  参数1.内容2.长度3.接口号
    bool    virtual NetInterFace(char *pData,int nLen,int nID)=0;   //网络接口  参数1.内容2.长度3.接口号

    //***************污染源类型******************
    // CDBSTJC m_dbstjc;
signals:

public slots:
};

#endif // CPROTOCOL_H
