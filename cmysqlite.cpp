#include "cmysqlite.h"
#include "coperationconfig.h"

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
    }
    return true;
}

bool CMySqlite::InsertRD(QString sCoding,QString sType,double dValue)
{
    QSqlQuery query(database);
    QString strSql="INSERT INTO c_rt_RealData (coding,type,nvalue) VALUES(\""+sCoding +"\",\""+sType+"\","+dValue+")";
    if(!query.exec(strSql))
    {
       COperationConfig::writelog(ERRLOGDBINSERTRD);
       return false;
    }
    return true;
}
