#ifndef CMYSQLITE_H
#define CMYSQLITE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
class CMySqlite : public QObject
{
    Q_OBJECT
public:
    explicit CMySqlite(QObject *parent = nullptr);
    QSqlDatabase database;
    bool init();
    bool InsertRD(QString sCoding,QString sType,double dValue);
    QSqlQuery SelRealData(QString coding , QDateTime begin , QDateTime end ,double &dMax,double &dMin,double &dAvg,double &dTotal,int &num);
    QSqlQuery SelRtdData(QString coding , QDateTime begin , QDateTime end ,double &dRtd);
signals:

public slots:
};

#endif // CMYSQLITE_H
