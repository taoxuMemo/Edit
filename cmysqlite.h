#ifndef CMYSQLITE_H
#define CMYSQLITE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "qdatatype.h"
class CMySqlite : public QObject
{
    Q_OBJECT
public:
    explicit CMySqlite(QObject *parent = nullptr);
    QSqlDatabase database;
    bool init();
    bool InsertRD(QString sCoding,QString sType,double dValue);
    bool InsertZSRD(QString sCoding,QString sType,double dValue,double dzsValue);
    bool InsertIPStatus(int nID,QString strIP,int nPort,int nStatus);  //存入网络连接状态
 //   bool InsertListRD(QList<stuRD>);
    bool InsertListZSRD(QList<stuZSRD>);
 //   bool InsertMNL();//向数据库中存储非数字量（模拟量及开关量）
    bool InsertInfo(QString sCoding,QString sType,QString sValue);
    QSqlQuery SelRealData(QString coding , QDateTime begin , QDateTime end ,double &dMax,double &dMin,double &dAvg,double &dTotal,int &num);
    QSqlQuery SelRtdData(QDateTime begin , QDateTime end);
    bool SelDataLen(QString , QString &);
signals:

public slots:
};

#endif // CMYSQLITE_H
