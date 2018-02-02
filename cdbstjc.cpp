#include "cdbstjc.h"
#include"coperationconfig.h"
#include "cmysqlite.h"
#include"qdatetime.h"
#include "mainwindow.h"
#include "qsqlquery.h"
#include "qdatatype.h"
CDBSTJC::CDBSTJC(QObject *parent) : CJCBase(parent)
{

}
bool CDBSTJC::NetInterFace(char *pData, int nLen, int nID)
{
    m_nNetID=nID;
    bool  bTag=this->CheckData(pData,nLen);
    if(bTag==false)
        return false;
    return true;
}
//参数：*pData指向数据段指针，nLen数据段结构长度
bool CDBSTJC::SerialInterFace(char *pData, int nLen, int nID)
{
  //  if(nLen<)
    int len=PackageCheck(pData,nLen);
    if(len==-1)
        return false;
    pData+=6;
    if(CheckData(pData,len)!=true)
    {
        COperationConfig::writelog(ERRLOGXYJXSJDYC);
        return false;
    }
    int nSJDJG=SJDJGZCB_QQBM_LEN+1+SJDJGZCB_STBM_LEN+1+SJDJGZCB_MLBM_LEN+1+SJDJGZCB_FWMM_LEN+1+SJDJGZCB_SBWYBS_LEN+1+SJDJGZCB_CFBJYDBZ_LEN+1;

    //解析数据
    char *couData=(pData+=nSJDJG);  //指向指令参数cp=
    if(strncmp(couData,"CP=&&",5)!=0)
    {
        COperationConfig::writelog(ERRLOGXYJXSJDCP);
        return false;
    }
    couData+=5;                         //couData指向数据区

    //int nLag=nLen-nSJDJG-5;
    int nValLen=nLen-nSJDJG-5;          //nValLen数据区长度
    QString sCoding,sType,sValue;
    char *pcouData=couData;
    for(int i=0;i<nValLen;i++)
    {
        if(*pcouData=='-')
        {
            *pcouData=0;
            sCoding=QString(QLatin1String(couData));
            pcouData++;
            couData=pcouData;
            continue;
        }else if(*pcouData=='=')
        {
            *pcouData=0;
            sType=QString(QLatin1String(couData));
            pcouData++;
            couData=pcouData;
            continue;
        }else if(*pcouData==',')
        {
            *pcouData=0;
            sValue=QString(QLatin1String(couData));
            pcouData++;
            couData=pcouData;
            //存入数据库


            sCoding="";
            sType="";
            sValue="";
            continue;
        }

    }
    return true;
}
//拼凑上传值的字符串
QString CDBSTJC::SpellStr(QString coding,int type, double dMax, double dMin, double dAvg, double dTotal)
{
    QString retstr;
    stuYZSBSZ stuYZ;
    stuSJCYZBMB  stuSJ;
    for(int i=0;i<20;i++)
    {
        if(strncmp(m_stuYZSBSZ[i].sCoding,coding.toLatin1().data(),6)==0)
        {
            stuYZ=m_stuYZSBSZ[i];
        }
        if(strncmp(m_stuSJCYZBMB[i].sCoding,coding.toLatin1().data(),6)==0)
        {
            stuSJ=m_stuSJCYZBMB[i];
        }
    }

    switch (type) {
    case 1:
        if(stuYZ.fcou==true)
            retstr+=coding+"-Cou="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        if(stuYZ.fmin==true)
            retstr+=coding+"-Min="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        if(stuYZ.favg==true)
            retstr+=coding+"-Avg="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        if(stuYZ.fmax==true)
            retstr+=coding+"-Max="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        break;
    case 2:
        if(stuYZ.hcou==true)
            retstr+=coding+"-Cou="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        if(stuYZ.hmin==true)
            retstr+=coding+"-Min="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        if(stuYZ.havg==true)
            retstr+=coding+"-Avg="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        if(stuYZ.hmax==true)
            retstr+=coding+"-Max="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        break;
    case 3:
        if(stuYZ.rcou==true)
            retstr+=coding+"-Cou="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        if(stuYZ.rmin==true)
            retstr+=coding+"-Min="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        if(stuYZ.ravg==true)
            retstr+=coding+"-Avg="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        if(stuYZ.rmax==true)
            retstr+=coding+"-Max="+CTool::douTostr(dTotal,stuSJ.sDataLen)+",";
        break;
    default:
        break;
    }
    retstr+=coding+"-Flag=N;";
    return retstr;
}
//****************计算最大最小累计值****
//type:1分钟上传 2：小时上传  3：天上传
bool  CDBSTJC::GetValue(int nType)
{

    QString strSpell;
//***********************拼接数据区字符串*******************************88
    QDateTime dt=QDateTime::currentDateTime();//查询终止时间
    QDateTime dtmin=dt;//查询起始时间
    double dFQMax=0,dFQMin=0,dFQAvg=0,dFQCou=0;//污水的相关值
    int num=0; //污水查询结果集的数量
    if(nType==1)
    {
        dtmin.addSecs(60*m_nFSBJG*-1);
    }else if(nType==2)
    {
        dtmin.addSecs(60*60*-1);

    }else if(nType==3)
    {
        dtmin.addDays(-1);
    }else
    {
        COperationConfig::writelog(ERRLOGTIMETYPE);
    }
    //  m_listJCYZ.size()

    QSqlQuery mysql=m_pMain->m_mySql.SelRealData("w00000",dtmin,dt,dFQMax,dFQMin,dFQAvg,dFQCou,num);

    for(int i=0;i<m_listJCYZ.length();i++)
    {
        double dTol=0,dMax=0,dMin=0,dAvg=0;
        int nNum=0;
        stuSJCYZBMB sjcy=  m_listJCYZ.at(i);
        if(strncmp(sjcy.sCoding,"w00000",6)==0)
        {
            if(num!=0)
                strSpell+=SpellUpStr(sjcy,nType,dFQMax,dFQMin,dFQAvg,dFQCou);
            continue;
        }
        bool bMark=false; //标志是否属于不求累计值的项
        m_pMain->m_mySql.SelRealData(sjcy.sCoding,dtmin,dt,dMax,dMin,dAvg,dTol,nNum);
        for(int j=0;j<9;j++)
        {
            if(strncmp(sjcy.sCoding,g_pSJCYZNOCOU[j],6)==0)
            {
                if(nNum!=0)//是否有该项数据
                {
                    strSpell+=SpellUpStr(sjcy,nType,dMax,dMin,dAvg);
                }
                bMark=true;
                break;
            }
        }
        if(bMark==true)
            continue;
        if(nNum!=0)//是否有该项数据
        {
            if(num!=0)     //该段时间是否有污水数据
                strSpell+=SpellUpStr(sjcy,nType,dMax,dMin,dAvg,dTol,dFQCou);
            else
                strSpell+=SpellUpStr(sjcy,nType,dMax,dMin,dAvg);
        }
    }

    return true;
}

void CDBSTJC::timerEvent(QTimerEvent *event)
{
    static int nTag=0;
    //设置秒上传间隔必须大于5
    QTime time=QTime::currentTime();
    if(m_bSSSJ==true &&nTag!=0 && nTag%m_nMSBJG==0)
    {

        ;
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
        //GetValue();
        ;
    }
    //小时上报
    if(m_bXSSJ==true && nMin==0&&nSec==0)
    {
        ;
    }
    //小时上报数据
    if(m_bRSJ==true && nHour==0 && nMin==0 && nSec==0)
    {

    }
}
