#include "cjcbase.h"
#include "math.h"
#include"qdatetime.h"
#include "mainwindow.h"
//#include"qdatatype.h"
CJCBase::CJCBase(QObject *parent) : CProtocol(parent)
{
    memset(m_sQQBM,0,SJDJGZCB_QQBM_LEN+1);
    memset(m_sXTBM,0,SJDJGZCB_STBM_LEN+1);
    memset(m_sMLBM,0,SJDJGZCB_MLBM_LEN+1);
    memset(m_sFWMM,0,SJDJGZCB_FWMM_LEN+1);
    m_nOverTime=0;
    m_nReCount=0;
    m_nMark=0;

}
bool CJCBase::CheckData(char *pData, int nLen)
{
    char *plData=pData;
    memcpy(m_sQQBM,pData,SJDJGZCB_QQBM_LEN);
    plData+=SJDJGZCB_QQBM_LEN;
    plData++;
    memcpy(m_sXTBM,plData,SJDJGZCB_STBM_LEN);
    plData+=SJDJGZCB_STBM_LEN;
    plData++;
    memcpy(m_sMLBM,pData,SJDJGZCB_MLBM_LEN);
    plData+=SJDJGZCB_MLBM_LEN;
    plData++;
    if(strncmp(m_sFWMM,plData,SJDJGZCB_FWMM_LEN)!=0)
    {
        //访问密码错误
        return false;
    }
    plData+=SJDJGZCB_FWMM_LEN;
    plData++;
    if(strncmp(g_DeviceMark,plData,SJDJGZCB_SBWYBS_LEN)!=0)
    {
        //唯一标识错误
        return false;
    }
    return true;
}
bool CJCBase::CommandData()
{
    int nCommand=0;
    for(int i=0;i<4;i++)
        nCommand+=(CTool::chartoint(m_sMLBM[3+i])*pow10(3-i));

}
bool  Splitinst(char *p,QString &a,QString &b) //拆分指令等号前后的
{
    char *pp=p;
    while(*p!=0)
    {
        if(*p=='=')
        {
            *p='0';
            p++;
            a=QString(QLatin1String(pp));
            b=QString(QLatin1String(p));
        }
        p++;
    }
    return false;
}
QString CJCBase::SpellUpDataTable(QString QQBM, QString MLBM, int nFlag,QString sDataArea)
{
    QString strSpell;

    strSpell="QN="+QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
    strSpell+=(";ST="+QString::number(m_nXTBM));    //系统编码
    strSpell+=(";CN="+MLBM);                        //命令编码
    strSpell+=(";"+QString(m_sFWMM));               //访问密码
    strSpell+=(";"+QString(m_sSBWYBS));             //设备唯一标识
    strSpell+=(";Flag="+QString::number(nFlag));    //拆分包应答标志
    strSpell+=(";CP=&&"+sDataArea+"&&");

    return strSpell;
}

QString CJCBase::SpellUpStr(stuSJCYZBMB stu, int type, double dMax, double dMin, double dAvg,double dTotal,double dStand)
{
    QString retstr;
    if(dTotal!=0 && dStand==0)
        dTotal/=1000;
    else if(dTotal!=0 && dStand!=0)
        dTotal=(dAvg*dStand)/1000000;

    QString strCou=QString(stu.sCoding)+"-Cou="+CTool::douTostr(dTotal,stu.sDataLen)+",";
    QString strMin=QString(stu.sCoding)+"-Min="+CTool::douTostr(dMin,stu.sDataLen)+",";
    QString strAvg=QString(stu.sCoding)+"-Avg="+CTool::douTostr(dAvg,stu.sDataLen)+",";
    QString strMax=QString(stu.sCoding)+"-Max="+CTool::douTostr(dMax,stu.sDataLen)+",";


    switch (type) {
    case 1:
        if(stu.stuYZ.fcou==true)
            retstr+=strCou;
        if(stu.stuYZ.fmin==true)
            retstr+=strMin;
        if(stu.stuYZ.favg==true)
            retstr+=strAvg;
        if(stu.stuYZ.fmax==true)
            retstr+=strMax;
        break;
    case 2:
        if(stu.stuYZ.hcou==true)
            retstr+=strCou;
        if(stu.stuYZ.hmin==true)
            retstr+=strMin;
        if(stu.stuYZ.havg==true)
            retstr+=strAvg;
        if(stu.stuYZ.hmax==true)
            retstr+=strMax;
        break;
    case 3:
        if(stu.stuYZ.rcou==true)
            retstr+=strCou;
        if(stu.stuYZ.rmin==true)
            retstr+=strMin;
        if(stu.stuYZ.ravg==true)
            retstr+=strAvg;
        if(stu.stuYZ.rmax==true)
            retstr+=strMax;
        break;
    default:
        break;
    }
    retstr+=QString(stu.sCoding)+"-Flag=N;";
    return retstr;
}
QString CJCBase::SpellUpStr(stuSJCYZBMB stu, double dRtd)
{
    QString retstr;
    retstr+=CTool::douTostr(dRtd,stu.sDataLen)+",";
    retstr+=QString(stu.sCoding)+"-Flag=N;";
    return retstr;
}
bool CJCBase::UploadReal()
{
    QString strSpell;
    //***********************拼接数据区字符串*******************************88
    QDateTime dt=QDateTime::currentDateTime();//查询终止时间
    QDateTime dtmin=dt;//查询起始时间
    dtmin.addSecs(m_nMSBJG*-1);
    for(int i=0;i<m_listJCYZ.length();i++)
    {
        double dRtd=0;
        int nNum=0;
        stuSJCYZBMB sjcy=  m_listJCYZ.at(i);
        if(sjcy.stuYZ.rtd==false)
            continue;
        m_pMain->m_mySql.SelRtdData(QString(sjcy.sCoding),dtmin,dt,dRtd);
        if(dRtd!=0)
            strSpell+=SpellUpStr(sjcy,dRtd);
    }

}
