#include "cqjcyz.h"
#include "coperationconfig.h"
#include "ccolsvr.h"
#include "cmysqlite.h"
#include "mainwindow.h"
#include"qdatetime.h"
CQJCYZ::CQJCYZ(QObject *parent) : CJCBase(parent)
{
    CJCBase::init();
    m_nTimerId = startTimer(1000);
}
CQJCYZ::~CQJCYZ()
{
    killTimer(m_nTimerId);
}
bool CQJCYZ::NetInterFace(char *pData, int nLen, int nID)
{
    m_nNetID=nID;
    int len=PackageCheck(pData,nLen);
    if(len==-1)
        return false;
    pData+=6;
    bool  bTag=this->CheckData(pData,len);
    if(bTag==false)
        return false;
    //提取系统编码整形
    QString sSTBM=QString(QLatin1String(m_sMLBM));
    QStringList sl=sSTBM.split("=");
    QString str=sl.at(1);
    int nSTBM=str.toInt();
    CommandCode(nSTBM);
    return true;
}
//****************计算最大最小累计值****
//type:1分钟上传 2：小时上传  3：天上传
bool  CQJCYZ::GetValue(int nType)
{
    QString strSpell;
    QString strMLBM;
    //***********************拼接数据区字符串*******************************88
    QDateTime dt=QDateTime::currentDateTime();//查询终止时间
    QDateTime dtmin=dt;//查询起始时间
    int nSecDiff=0;//分钟相差多少秒
    double dFQMax=0,dFQMin=0,dFQAvg=0,dFQCou=0;//废气的相关值
    int nFQ=0; //废气查询结果集的数量
    if(nType==1)
    {
        nSecDiff=60*m_nFSBJG*-1;
        dtmin.addSecs(nSecDiff);
        strMLBM="2051";
    }else if(nType==2)
    {
        nSecDiff=60*60;
        dtmin.addSecs(nSecDiff);
        strMLBM="2061";

    }else if(nType==3)
    {
        nSecDiff=60*60*24;
        dtmin.addSecs(nSecDiff);
        strMLBM="2031";
    }else
    {
        COperationConfig::writelog(ERRLOGTIMETYPE);
    }
    //  m_listJCYZ.size()
    //添加DataTime字段
    strSpell+="DataTime="+QDateTime::currentDateTime().toString("yyyyMMddhhmmss")+";";

    QSqlQuery mysql=m_pMain->m_mySql.SelRealData("a00000",dtmin,dt,dFQMax,dFQMin,dFQAvg,dFQCou,nFQ);
    if(nFQ>0)
    {
        dFQCou=dFQAvg*nSecDiff;   //废气总量=废气平均值*采集周期
        for(int i=0;i<ITEMSTULEN;i++)
        {
            if(strncmp(m_stuSJCYZBMB[i].sCoding,"a00000",6)==0)
            {
                strSpell+=SpellUpStr(m_stuSJCYZBMB[i],nType,dFQMax,dFQMin,dFQAvg,dFQCou*1000);
                break;
            }
        }

    }

    for(int i=0;i<3;i++) //气体监测项需要则算的
    {
        double dMax=0,dMin=0,dAvg=0,dCou=0,dzsMax=0,dzsMin=0,dzsAvg=0;//气体因子的相关值
        int nNum=0; //因子查询结果集的数量
        QSqlQuery mysql=m_pMain->m_mySql.SelRealData(g_QTJCZSCoding[i],dtmin,dt,dMax,dMin,dAvg,dCou,nNum);
        if(nNum>0) //确定是否有该项监测因子数据
        {
            if(nFQ>0)//是否有废气数据以便计算污染项总量
            {
                dCou=dAvg*dFQCou;
            }
            dzsMax=zsValue(dMax);
            dzsMin=zsValue(dMin);
            dzsAvg=zsValue(dAvg);
            for(int j=0;j<ITEMSTULEN;j++)
            {
                if(strncmp(m_stuSJCYZBMB[j].sCoding,g_QTJCZSCoding[i],6)==0)
                {
                    strSpell+=SpellUpStr(m_stuSJCYZBMB[j],nType,dFQMax,dFQMin,dFQAvg,dFQCou,dzsMax,dzsMin,dzsAvg);
                    break;
                }
            }
        }

    }
    QString strQQBM=QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
    QString strDataTable=SpellUpDataTable(strQQBM,strMLBM,4,strSpell);//拼接数据段
    QByteArray  baSpell=SpellPackage(strDataTable); //拼接整个包
    TcpSendVal(baSpell.data(),baSpell.size());
}

bool CQJCYZ::GetMinValue()
{
    QString strSpell;
    QString strMLBM="2051";
    //***********************拼接数据区字符串*******************************88
    QDateTime dt=QDateTime::currentDateTime();//查询终止时间
    QDateTime dtmin=dt;//查询起始时间
    int nSecDiff=60*m_nFSBJG*-1;//分钟相差多少秒
    dtmin.addSecs(nSecDiff);//起始时间
    double dFQMax=0,dFQMin=0,dFQAvg=0,dFQCou=0;//废气的相关值
    int nFQ=0; //气体查询结果集的数量
    strSpell+="DataTime="+QDateTime::currentDateTime().toString("yyyyMMddhhmmss")+";";
    QSqlQuery mysql=m_pMain->m_mySql.SelRealData("a00000",dtmin,dt,dFQMax,dFQMin,dFQAvg,dFQCou,nFQ);
    if(nFQ>0)
        dFQCou=dFQAvg*nSecDiff;   //废气总量=废气平均值*采集周期

    return true;
}



//参数：*pData指向数据段指针，nLen数据段结构长度
bool CQJCYZ::SerialInterFaceNew(char *pData, int nLen, int nID)
{
    CColSvr cs;
    if(cs.setData(pData,nLen)==false)
    {

        COperationConfig::writelog(ERRORSERIALPROTOCOL,QString::number(cs.m_nErrCode).toLatin1().data());
        return false;
    }
    if(cs.m_nCN==2011)
    {
        QList <stuCol> ls=cs.getlist();
        for(int i=0;i<ls.size();i++)
        {
            stuCol stu=ls.at(i);
            if(strncmp(stu.sName,"a01012",6)==0)//烟气温度
                m_dTS=stu.dvalue;
            if(strncmp(stu.sName,"a01013",6)==0)//烟气压力
                m_dPS=stu.dvalue;
            if(strncmp(stu.sName,"a01014",6)==0)//烟气湿度
                m_dXSW=stu.dvalue;
            if(strncmp(stu.sName,"a21002",6)==0 || strncmp(stu.sName,"a21026",6)==0 || strncmp(stu.sName,"a34013",6)==0)
            {
                stu.dzsvalue = zsValue(stu.dvalue);
                m_pMain->m_mySql.InsertZSRD(QString(QLatin1String(stu.sName)),QString(QLatin1String(stu.sType)),stu.dvalue,stu.dzsvalue);
            }else
            {
                m_pMain->m_mySql.InsertRD(QString(QLatin1String(stu.sName)),QString(QLatin1String(stu.sType)),stu.dvalue);
            }

        }
    }else if(cs.m_nCN==3020)
    {
        QList <stuInfo> ls=cs.getlistinfo();
        for(int i=0;i<ls.size();i++)
        {
            stuInfo stu=ls.at(i);
            m_pMain->m_mySql.InsertInfo(QString(QLatin1String(stu.sName)),QString(QLatin1String(stu.sType)),QString(QLatin1String(stu.sValue)));
        }
    }
    if(cs.m_nErrCode!=0)
    {
        COperationConfig::writelog(ERRORSERIALPROTOCOL,QString::number(cs.m_nErrCode).toLatin1().data());
    }
    return true;
}
double CQJCYZ::zsValue(double dZS)
{
    double dVal=dZS*(273/(273+m_dTS))*((m_dBA+m_dPS)/101325)*(1-m_dXSW);
    return dVal;
}
void CQJCYZ::timerEvent(QTimerEvent *event)
{
    static int nTag=0;
    //设置秒上传间隔必须大于5
    QTime time=QTime::currentTime();
    if(m_bSSSJ==true && nTag!=0 && nTag%m_nMSBJG==0)
    {
        UploadReal();
    }
    if(nTag==3600)
        nTag=0;
    else
        nTag++;
    //上传水监测时数据
    int nSec=time.second();
    int nMin=time.minute();
    int nHour=time.hour();
    //分钟上报
    if(m_bFZSJ==true && nSec==0 && nMin%m_nFSBJG!=0)//添加上报标记
    {
        GetValue(1);
        ;
    }
    //小时上报
    if(m_bXSSJ==true && nMin==0&&nSec==0)
    {
        GetValue(2);
    }
    //小时上报数据
    if(m_bRSJ==true && nHour==0 && nMin==0 && nSec==0)
    {
        GetValue(3);
    }
}
