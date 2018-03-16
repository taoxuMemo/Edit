#include "cmysqlite.h"
#include "coperationconfig.h"
#include "qdatetime.h"
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

QSqlQuery CMySqlite::SelRealData(QString coding , QDateTime begin , QDateTime end,double &dMax,double &dMin,double &dAvg,double &dTotal,int &num)
{
    QSqlQuery query(database);
    if(begin>=end)
    {
        COperationConfig::writelog(ERRLOGDBSELTIME);
        //       return NULL;
    }
    QString select_sql = "select * from c_rt_RealData where coding=\""+coding+"\" and type=\"Rtd\" and stime>\""+begin.toString("yyyy-MM-dd hh:mm:ss")+"\" and stime<\""+end.toString("yyyy-MM-dd hh:mm:ss")+"\"";
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
        while (query.next()) {
            ret=query.value(0).toString();
            return true;
        }
    }
    COperationConfig::writelog(ERRLOGDBDATALEN,select_sql.toLatin1().data());
    return false;
}
