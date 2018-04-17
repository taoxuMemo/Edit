#include "cmysqlite.h"
#include "coperationconfig.h"
#include "qdatetime.h"
#include<QMessageLogger>
#include <QDebug>
CMySqlite::CMySqlite(QObject *parent) : QObject(parent)
{
    database=QSqlDatabase::addDatabase("QSQLITE");
}

bool CMySqlite::init()
{
    database.setDatabaseName("scy.db");
    if(!database.open())
    {
        COperationConfig::writelog(ERRLOGDBOPENFAIL);
        return false;
    }
    return true;
}

bool CMySqlite::InsertRD(QString sCoding,QString sType,double dValue)
{
    QSqlQuery query(database);
    QString strSql="INSERT INTO c_rt_RealData (coding,type,nvalue) VALUES(\""+sCoding +"\",\""+sType+"\","+QString::number(dValue)+")";
    if(!query.exec(strSql))
    {
        COperationConfig::writelog(ERRLOGDBINSERTRD,strSql.toLatin1().data());
        return false;
    }
    return true;
}
bool CMySqlite::InsertZSRD(QString sCoding, QString sType, double dValue, double dzsValue)
{
    QSqlQuery query(database);
    QString strSql="INSERT INTO c_rt_RealData (coding,type,nvalue,nzsvalue) VALUES(\""+sCoding +"\",\""+sType+"\","+QString::number(dValue)+","+QString::number(dzsValue)+")";
    if(!query.exec(strSql))
    {
        COperationConfig::writelog(ERRLOGDBINSERTZSRD,strSql.toLatin1().data());
        return false;
    }
    return true;
}

bool CMySqlite::InsertListZSRD(QList<stuZSRD> ls)
{
    QTime time;
    time.start();
    QSqlQuery query(database);

    //    query.exec("PRAGMA synchronous = OFF;");

    query.exec("begin;");
    //   database.commit();
    //    database.transaction();
    //   query.prepare("INSERT INTO c_rt_RealData(coding,type,nvalue,nzsvalue) VALUES(?,?,?,?)");
    //   QVariantList ucoding,utype,unvalue,unzsvalue;
    // qDebug()<<time.elapsed()<<"ss1";
    for(int i=0;i<ls.size();i++)
    {
        stuZSRD rd=ls.at(i);
        time.start();
        QString strSql="INSERT INTO c_rt_RealData(coding,type,nvalue,nzsvalue) VALUES('"+rd.sCoding +"','"+rd.sType+"',"+QString::number(rd.dValue)+","+QString::number(rd.dzsValue)+")";
        qDebug()<<strSql<<"s";
        time.start();
        if(!query.exec(strSql))
        {
            COperationConfig::writelog(ERRLOGDBINSERTZSRD,strSql.toLatin1().data());
            return false;
        }

        //        ucoding<<rd.sCoding;
        //        utype<<rd.sType;
        //        unvalue<<rd.dValue;
        //        unzsvalue<<rd.dzsValue;
        //   qDebug()<<time.elapsed()<<"s";
    }
    //    qDebug()<<time.elapsed()<<"ss2";
    //    query.addBindValue(ucoding);
    //    query.addBindValue(utype);
    //    query.addBindValue(unvalue);
    //    query.addBindValue(unzsvalue);
    //    query.execBatch();
    //    database.commit();


    query.exec("commit;");
    qDebug()<<time.elapsed()<<"ss3";
    return false;
}

bool CMySqlite::InsertInfo(QString sCoding, QString sType, QString sValue)
{
    QSqlQuery query(database);
    QString strSql="INSERT INTO c_rt_InfoData (coding,type,svalue) VALUES(\""+sCoding +"\",\""+sType+"\","+sValue+")";
    if(!query.exec(strSql))
    {
        COperationConfig::writelog(ERRLOGDBINSERTINFO,strSql.toLatin1().data());
        return false;
    }
    return true;
}

bool CMySqlite::InsertIPStatus(int nID, QString strIP, int nPort, int nStatus)
{
    QSqlQuery query(database);
    QString strSql="INSERT INTO c_rt_IPStatus (number,ipaddr,port,status) VALUES("
            +QString::number(nID) +",'"+strIP+"',"+QString::number(nPort)+","+QString::number(nStatus)+")";

    if(!query.exec(strSql))
    {
        COperationConfig::writelog(ERRLOGDBIPSTATUS,strSql.toLatin1().data());
        return false;
    }
    return true;
}

QSqlQuery CMySqlite::SelRealData(QString coding , QDateTime begin , QDateTime end,double &dMax,double &dMin,double &dAvg,double &dTotal,int &num)
{
    QSqlQuery query(database);
    if(begin>=end)
    {
        COperationConfig::writelog(ERRLOGDBSELTIME);
        //       return NULL;
    }
    QString select_sql = "select * from c_rt_RealData where coding='"+coding+"' and type='Rtd' and stime>'"+begin.toString("yyyy-MM-dd hh:mm:ss")+"' and stime<'"+end.toString("yyyy-MM-dd hh:mm:ss")+"'";
    qDebug()<<select_sql;
    if(!query.exec(select_sql))
    {
        COperationConfig::writelog(ERRLOGDBSELEXEC,select_sql.toLatin1().data());
        //        return NULL;
    }
    num=0;
    while (query.next()) {
        double country = query.value(3).toDouble();
        if(num==0)
        {
            dMax=dMin=dTotal=country;
        }else
        {
            dTotal+=country;
            dMax=((dMax>country)?dMax:country);
            dMin=((dMin<country)?dMin:country);
        }
        num++;
    }
    dAvg=dTotal/num;
    return query;

}

QSqlQuery CMySqlite::SelRtdData( QDateTime begin, QDateTime end)
{
    QSqlQuery query(database);
    QString select_sql = "select * from c_rt_RealData where  stime>\""+begin.toString("yyyy-MM-dd hh:mm:ss")+"\" and stime<\""+end.toString("yyyy-MM-dd hh:mm:ss")+"\"  group by coding";
    if(!query.exec(select_sql))
    {
        COperationConfig::writelog(ERRLOGDBSELEXEC,select_sql.toLatin1().data());
        //        return NULL;
    }

    return query;
}

bool CMySqlite::SelDataLen(QString coding, QString & ret)
{
    QSqlQuery query(database);
    QString select_sql = "select precision from factorInfo where  code=\""+coding+"\"";
    if(!query.exec(select_sql))
    {
        COperationConfig::writelog(ERRLOGDBDATALEN,select_sql.toLatin1().data());
    }

    while (query.next()) {
        ret=query.value(0).toString();
        return true;
    }
    return false;
}
