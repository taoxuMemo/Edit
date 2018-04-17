#include "cjcbase.h"
#include "math.h"
#include"qdatetime.h"
#include "mainwindow.h"
//#include"qdatatype.h"
CJCBase::CJCBase(QObject *parent) : CProtocol(parent)
{
    //   m_pQQBM=new char[21];
    memset(m_sQQBM,0,SJDJGZCB_QQBM_LEN+1);
    memset(m_sXTBM,0,SJDJGZCB_STBM_LEN+1);
    memset(m_sMLBM,0,SJDJGZCB_MLBM_LEN+1);
    memset(m_sFWMM,0,SJDJGZCB_FWMM_LEN+1);
    strncpy(m_sFWMM,"PW=123456",SJDJGZCB_FWMM_LEN);
    m_nOverTime=0;
    m_nReCount=0;
    m_nMark=0;

    QString str=m_pMain->m_pOpera->getText("col","type");

}
bool CJCBase::init()
{
    QString str=m_pMain->m_pOpera->getText("col","type");
    strncpy(m_sXTBM,str.toLatin1().data(),str.size());

    str=m_pMain->m_pOpera->getText("col","sysid");
    strncpy(m_sSBWYBS,str.toLatin1().data(),str.size());

    str=m_pMain->m_pOpera->getText("col","passwd");
    strncpy(m_sFWMM,str.toLatin1().data(),str.size());

    str=m_pMain->m_pOpera->getText("col","type");
    strncpy(m_sXTBM,str.toLatin1().data(),str.size());

    str=m_pMain->m_pOpera->getText("col","Rtd");
    m_nMSBJG=str.toInt();

    str=m_pMain->m_pOpera->getText("col","min");
    m_nFSBJG=str.toInt();

    str=m_pMain->m_pOpera->getText("col","bRtd");
    m_bSSSJ=str.toInt();

    str=m_pMain->m_pOpera->getText("col","bmin");
    m_bFZSJ=str.toInt();

    str=m_pMain->m_pOpera->getText("col","bhour");
    m_bXSSJ=str.toInt();

    str=m_pMain->m_pOpera->getText("col","bday");
    m_bRSJ=str.toInt();
    for(int i=0;i<ITEMSTULEN;i++)
    {
        m_pMain->m_pOpera->ReadItem(&m_stuSJCYZBMB[i].stuYZ,i+1);
        strncpy(m_stuSJCYZBMB[i].sCoding,m_stuSJCYZBMB[i].stuYZ.sCoding,7);
        //   m_stuSJCYZBMB[i].sCoding=m_stuSJCYZBMB[i].stuYZ.sCoding;
        QString strN=QString(m_stuSJCYZBMB[i].sCoding);
        if(strN.length()==6)
        {
            QString sDLen;
            if(m_pMain->m_mySql.SelDataLen(strN,sDLen))
            {
                strncpy(m_stuSJCYZBMB[i].sDataLen,sDLen.toLatin1().data(),sDLen.length());
            }
        }
    }
    return true;
}
bool CJCBase::TcpSendVal(char *pData, int nLen, int nID)
{
    m_pMain->AddRD(nLen,1);
    COperationConfig::writeSendRD(QString(QLatin1String(pData,nLen)));
    if(nID==-1)
    {
        for(int i=0;i<6;i++)
        {
            if(m_pMain->m_pMySocket[i]!=NULL &&m_pMain->m_pMySocket[i]->isConnect==true)
            {
                if(m_pMain->m_pMySocket[i]->MySend( pData, nLen)==false)
                {
                    QString str="断开连接----"+QString(m_pMain->m_pMySocket[i]->m_IPAddr.sIP)+":"+QString::number(m_pMain->m_pMySocket[i]->m_IPAddr.nPort);
                    // return false;
                }
            }
        }
    }else if(nID>=0 && nID<=6)
    {
        if(m_pMain->m_pMySocket[nID]!=NULL &&m_pMain->m_pMySocket[nID]->isConnect==true)
        {
            if(m_pMain->m_pMySocket[nID]->MySend( pData, nLen)==false)
            {
                QString str="断开连接----"+QString(m_pMain->m_pMySocket[nID]->m_IPAddr.sIP)+":"+QString::number(m_pMain->m_pMySocket[nID]->m_IPAddr.nPort);
                return false;
            }
        }else
        {return false;}

    }
    return true;
}
bool CJCBase::CheckData(char *pData, int nLen)
{
    //   m_nPNUM=10;
    //   m_pQQBM=new char[22];
    char *plData=pData;
    //   char sQQBM[SJDJGZCB_QQBM_LEN+1];
    strncpy(m_sQQBM,pData,SJDJGZCB_QQBM_LEN);
    //  strncpy(m_pQQBM,sQQBM,5);
    plData+=SJDJGZCB_QQBM_LEN;
    plData++;
    strncpy(m_sXTBM,plData,SJDJGZCB_STBM_LEN);
    plData+=SJDJGZCB_STBM_LEN;
    plData++;
    strncpy(m_sMLBM,plData,SJDJGZCB_MLBM_LEN);
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
        ;
        //唯一标识错误
        //  return false;
    }
    plData+=(6+1+3+2);
    m_nDataArea=nLen-20-1-5-1-7-1-9-1-27-1-6-1-5;
    memset(m_sDataArea,0,2046);
    strncpy(m_sDataArea,plData,m_nDataArea);
    return true;
}
bool CJCBase::CommandData()
{
    int nCommand=0;
    for(int i=0;i<4;i++)
        nCommand+=(CTool::chartoint(m_sMLBM[3+i])*pow10(3-i));
    return true;

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
QList<QString> CJCBase::SplitMH(char *pd, int nlen)
{
    char p[1024];
    memset(p,0,1024);
    strncpy((char *)p,pd,nlen);
    char *pp=(char *)p;

    QList<QString> ls;
    for(int i=0;i<nlen;i++)
    {
        if(p[i]==';')
        {
            p[i]=0;
            ls.insert(0,QString(QLatin1String(pp)));
            pp=&p[i+1];
        }
        if(i==nlen-1)
        {
            ls.insert(0,QString(QLatin1String(pp)));
        }
    }
}
QString CJCBase::SpellUpDataTable(QString QQBM, QString MLBM, int nFlag,QString sDataArea)
{
    QString strSpell;

    //  strSpell="QN="+QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
    strSpell=("QN="+QQBM);                          //请求编码
    strSpell+=(";ST="+QString(m_sXTBM));    //系统编码
    strSpell+=(";CN="+MLBM);                        //命令编码
    strSpell+=(";PW="+QString(m_sFWMM));               //访问密码
    strSpell+=(";MN="+QString(m_sSBWYBS));             //设备唯一标识
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

QString CJCBase::SpellUpStr(stuSJCYZBMB stu, int type, double dMax, double dMin, double dAvg, double dTotal, double dMaxZS, double dMinZS, double dAvgZS)
{
    QString retstr;

    QString strCou=QString(QLatin1String(stu.sCoding))+"-Cou="+CTool::douTostr(dTotal,stu.sDataLen)+",";

    QString strMin=QString(QLatin1String(stu.sCoding))+"-Min="+CTool::douTostr(dMin,stu.sDataLen)+",";
    QString strAvg=QString(QLatin1String(stu.sCoding))+"-Avg="+CTool::douTostr(dAvg,stu.sDataLen)+",";
    QString strMax=QString(QLatin1String(stu.sCoding))+"-Max="+CTool::douTostr(dMax,stu.sDataLen)+",";

    QString strzsMin=QString(QLatin1String(stu.sCoding))+"-ZsMin="+CTool::douTostr(dMinZS,stu.sDataLen)+",";
    QString strzsAvg=QString(QLatin1String(stu.sCoding))+"-ZsAvg="+CTool::douTostr(dAvgZS,stu.sDataLen)+",";
    QString strzsMax=QString(QLatin1String(stu.sCoding))+"-ZsMax="+CTool::douTostr(dMaxZS,stu.sDataLen)+",";

    switch (type) {
    case 1:
        if(stu.stuYZ.fcou==true)
            retstr+=strCou;
        if(stu.stuYZ.fmin==true)
            retstr+=strMin;
        retstr+=strzsMin;
        if(stu.stuYZ.favg==true)
            retstr+=strAvg;
        retstr+=strzsAvg;
        if(stu.stuYZ.fmax==true)
            retstr+=strMax;
        retstr+=strzsMax;
        break;
    case 2:
        if(stu.stuYZ.hcou==true)
            retstr+=strCou;
        if(stu.stuYZ.hmin==true)
            retstr+=strMin;
        retstr+=strzsMin;
        if(stu.stuYZ.havg==true)
            retstr+=strAvg;
        retstr+=strzsAvg;
        if(stu.stuYZ.hmax==true)
            retstr+=strMax;
        retstr+=strzsMax;
        break;
    case 3:
        if(stu.stuYZ.rcou==true)
            retstr+=strCou;
        if(stu.stuYZ.rmin==true)
            retstr+=strMin;
        retstr+=strzsMin;
        if(stu.stuYZ.ravg==true)
            retstr+=strAvg;
        retstr+=strzsAvg;
        if(stu.stuYZ.rmax==true)
            retstr+=strMax;
        retstr+=strzsMax;
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
    retstr+=QString(stu.sCoding)+"-Rtd=";
    retstr+=CTool::douTostr(dRtd,stu.sDataLen)+",";
    retstr+=QString(stu.sCoding)+"-Flag=N;";
    return retstr;
}
//发送实时数据
bool CJCBase::UploadReal()
{
    QString strSpell;
    //***********************拼接数据区字符串*******************************88
    QDateTime dt=QDateTime::currentDateTime();//查询终止时间
    QDateTime dtmin=dt;//查询起始时间
    dtmin.addSecs(m_nMSBJG*-1);
    QSqlQuery query=m_pMain->m_mySql.SelRtdData(dtmin,dt);
    while (query.next()) {
        QString strC =query.value(1).toString();
        double dVal =query.value(3).toDouble();
        for(int i=0;m_listJCYZ.length();i++)
        {
            if(QString(m_stuYZSBSZ[i].sCoding).compare(strC)==0 && m_stuYZSBSZ[i].rtd==true);
            //       strSpell+=SpellUpStr(sjcy,dVal);
        }

    }

    if(strSpell.length()!=0)
    {
        QString strQQBM=QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
        QString strDataTable=SpellUpDataTable(strQQBM,"2011",4,strSpell);//拼接数据段
        QByteArray  baSpell=SpellPackage(strDataTable); //拼接整个包
        TcpSendVal(baSpell.data(),baSpell.size());
    }
    return true;

}
//*******************************************与上位机通讯协议解析*******************************************************************
//获取命令编码  pData数据段结构组成表   nLen数据段结构组成表长度
int CJCBase::GetCN(char *pData, int nLen)
{
    if(nLen<(20+5+7))
    {
        COperationConfig::writelog(ERRORSJDJGZCCNLEN,QString::number(nLen).toLatin1().data());
        return -1;
    }
    char * data=pData;
    data+=(20+5);
    if(*data=='C' && *(data+1)=='N' && *(data+2)=='=')
    {
        char nData[5];
        memset(nData,0,5);
        strncpy(nData,(data+3),4);
        int nCommand=atoi(nData);
        return nCommand;
    }else
    {
        char errData[8];
        memcpy(errData,0,8);
        strncpy(errData,data,7);
        COperationConfig::writelog(ERRORSJDJGZCCNNAME,errData);
        return -2;
    }
}
QString  CJCBase::GetQN(char *pData, int nLen)
{
    ;
}
int  CJCBase::GetST(char *pData, int nLen)
{
    ;
}
QString  CJCBase::GetPW(char *pData, int nLen)
{
    ;
}
QString  CJCBase::GetMN(char *pData, int nLen)
{
    ;
}
bool CJCBase::CommandCode(int nCommand)
{
    switch(nCommand)
    {
    case 1000:
        Ans1000();
        break;
    case 1011:
        Ans1011();
        break;
    case 1012:
        break;
    case 1061:
        Ans1061();
        break;
    case 1062:
        Ans1062();
        break;
    case 1063:
        Ans1063();
        break;
    case 1064:
        Ans1064();
        break;
    case 1072:
        Ans1072();
        break;
    case 2011:
        Ans2011();
        break;
    case 2012:
        break;
    case 2021:
        break;
    case 2022:
        break;
    case 2031:
        break;
    case 2041:
        break;
    case 2051:
        break;
    case 2061:
        break;
    case 3011:
        break;
    case 3012:
        break;
    case 3013:
        break;
    case 3014:
        break;
    case 3015:
        break;
    case 3016:
        break;
    case 3017:
        break;
    case 3018:
        break;
    case 3019:
        break;
    case 3020:
        break;
    case 3021:
        break;
    case 9013:
        break;
    case 9014:
        AnsData();
        break;
    default:
        break;

    }
}
//发送函数及重发判断
bool CJCBase::SendData()
{
    QDateTime dt=QDateTime::currentDateTime();
    int listCnt=m_listSend.size();
    for(int i=0;i<listCnt;i++)
    {
        UpDataStu uds=m_listSend.takeAt(0);
        if(uds.nCnt==0)//第一次发送
        {
            //发送数据
            if(TcpSendVal(uds.sData,uds.nLen,uds.nIP)==false)
                continue;
            //**************
            uds.nCnt++;
            QString strTime1=dt.toString("yyyy-MM-dd hh:mm:ss");
            QByteArray ba=strTime1.toLatin1();
            strncpy((char *)uds.sTime,ba.data(),20);
            m_listSend.append(uds);

        }
        else if(uds.nCnt<m_nReCount)//大于重发次数
        {
            QString strTime=QString(QLatin1String((char *)uds.sTime));
            QDateTime  dt1 = QDateTime::fromString(strTime, "yyyy-MM-dd hh:mm:ss");
            int nSec=dt1.secsTo(dt);
            if(nSec>m_nOverTime)
            {
                //发送数据
                if(TcpSendVal(uds.sData,uds.nLen,uds.nIP)==false)
                    continue;
                //**************
                uds.nCnt++;
                QString strTime1=dt.toString("yyyy-MM-dd hh:mm:ss");
                QByteArray ba=strTime1.toLatin1();
                strncpy((char *)uds.sTime,ba.data(),20);
            }
            m_listSend.append(uds);
        }
    }
}
//接收到相应删除数据
bool CJCBase::AnsData()
{
    QString str=QString(QLatin1String(m_sXTBM));
    QStringList sl=str.split("=");
    QString str1=sl.at(1);
    int nXTBM=str1.toInt();
    if(nXTBM!=91)
    {
        COperationConfig::writelog(ERRORSTERROR,str1.toLatin1().data());
        return false;
    }
    for(int i=0;i<m_listSend.size();i++)
    {
        UpDataStu stu=m_listSend.at(i);
        if(stu.nIP==m_nNetID)
        {
            //QString str=QString(QLatin1String(stu.sQN));
            //if(strQN.compare(str)==0)
            if(strncmp(stu.sQN,m_sQQBM,20)==0)
            {
                m_listSend.removeAt(i);
                break;
            }
        }
    }
    return true;
}
//***********************************答复上位机平台**************************
bool CJCBase::Ans1000()
{


    QString strPD=QString(QLatin1String(m_sDataArea));
    QStringList list1 = strPD.split(";");

    for(int i=0;i<list1.size();i++)
    {
        QString str1=list1.at(i);
        QStringList listA=str1.split("=");
        if(listA.size()==2)
        {
            QString strA=listA.at(0);
            QString strB=listA.at(1);
            if(strA.compare("OverTime")==0)
            {
                m_nOverTime=strB.toInt();
            }
            if(strA.compare("ReCount")==0)
            {
                m_nReCount=strB.toInt();
            }

        }
    }
    //相应上位机
    QString strQQYD=SpellUpDataTable(QString(m_sQQBM),"9011",4,"QnRtn=1");//请求应答数据
    QByteArray  baSpell=SpellPackage(strQQYD); //拼接整个包


    QString strZXJG=SpellUpDataTable(QString(m_sQQBM),"9012",4,"ExeRtn=1");//执行结果数据
    QByteArray  baSpell1=SpellPackage(strZXJG); //拼接整个包

    return true;
}
bool CJCBase::Ans1011()
{
    QString strQQYD=SpellUpDataTable(QString(m_sQQBM),"9011",4,"QnRtn=1");//请求应答数据
    QByteArray  baSpell=SpellPackage(strQQYD); //拼接整个包

    QString strZXJG=SpellUpDataTable(QString(m_sQQBM),"9012",4,"ExeRtn=1");//执行结果数据
    QByteArray  baSpell1=SpellPackage(strZXJG); //拼接整个包
    return true;
}
bool CJCBase::Ans1012()
{

    QString strPD=QString(QLatin1String(m_sDataArea));
    QStringList list1 = strPD.split(";");
    QString sYQYB,sTime;//1仪器仪表ID ，2系统时间。
    for(int i=0;i<list1.size();i++)
    {
        QString str1=list1.at(i);
        QStringList listA=str1.split("=");
        if(listA.size()==2)
        {
            QString strA=listA.at(0);
            QString strB=listA.at(1);
            if(strA.compare("PolId")==0)
                sYQYB=strB;
            if(strA.compare("SystemTime")==0)
                sTime=strB;
        }
    }
    if(sYQYB.length()!=0)
    {
        ;//设置仪器仪表的系统时间
    }else
    {
        ;//设置本机系统时间
    }


    QString strQQYD=SpellUpDataTable(QString(m_sQQBM),"9011",4,"QnRtn=1");//请求应答数据
    QByteArray  baSpell=SpellPackage(strQQYD); //拼接整个包
    TcpSendVal(baSpell.data(),baSpell.size(),m_nNetID);

    QString strZXJG=SpellUpDataTable(QString(m_sQQBM),"9012",4,"ExeRtn=1");//执行结果数据
    QByteArray  baSpell1=SpellPackage(strZXJG); //拼接整个包
    TcpSendVal(baSpell1.data(),baSpell1.size(),m_nNetID);
    return true;
}

bool CJCBase::Ans1061()
{

    QString strQQYD=SpellUpDataTable(QString(m_sQQBM),"9011",4,"QnRtn=1");//请求应答数据
    QByteArray  baSpell=SpellPackage(strQQYD); //拼接整个包
    TcpSendVal(baSpell.data(),baSpell.size(),m_nNetID);

    QString strN="RtdInterval="+QString::number(m_nMSBJG);
    QString strFSXY=SpellUpDataTable(QString(m_sQQBM),"1061",4,strN);//发送相应
    QByteArray  baSpell1=SpellPackage(strFSXY); //拼接整个包
    TcpSendVal(baSpell1.data(),baSpell1.size(),m_nNetID);

    QString strZXJG=SpellUpDataTable(QString(m_sQQBM),"9012",4,"ExeRtn=1");//执行结果数据
    QByteArray  baSpell2=SpellPackage(strZXJG); //拼接整个包
    TcpSendVal(baSpell2.data(),baSpell2.size(),m_nNetID);
    return true;
}

bool CJCBase::Ans1062()
{

    QString strPD=QString(QLatin1String(m_sDataArea));
    QStringList list1 = strPD.split("=");
    if(list1.size()==2)
    {
        QString strA=list1.at(0);
        QString strB=list1.at(1);
        if(strA.compare("RtdInterval")==0)
            m_nMSBJG=strB.toInt();
    }

    QString strQQYD=SpellUpDataTable(QString(m_sQQBM),"9011",4,"QnRtn=1");//请求应答数据
    QByteArray  baSpell=SpellPackage(strQQYD); //拼接整个包
    TcpSendVal(baSpell.data(),baSpell.size(),m_nNetID);

    QString strZXJG=SpellUpDataTable(QString(m_sQQBM),"9012",4,"ExeRtn=1");//执行结果数据
    QByteArray  baSpell1=SpellPackage(strZXJG); //拼接整个包
    TcpSendVal(baSpell1.data(),baSpell1.size(),m_nNetID);
    return true;
}
bool CJCBase::Ans1063()
{
    QString strQQYD=SpellUpDataTable(QString(m_sQQBM),"9011",4,"QnRtn=1");//请求应答数据
    QByteArray  baSpell=SpellPackage(strQQYD); //拼接整个包
    TcpSendVal(baSpell.data(),baSpell.size(),m_nNetID);

    QString strN="RtdInterval="+QString::number(m_nFSBJG);
    QString strFSXY=SpellUpDataTable(QString(m_sQQBM),"1063",4,strN);//发送相应
    QByteArray  baSpell1=SpellPackage(strFSXY); //拼接整个包
    TcpSendVal(baSpell1.data(),baSpell1.size(),m_nNetID);

    QString strZXJG=SpellUpDataTable(QString(m_sQQBM),"9012",4,"ExeRtn=1");//执行结果数据
    QByteArray  baSpell2=SpellPackage(strZXJG); //拼接整个包
    TcpSendVal(baSpell2.data(),baSpell2.size(),m_nNetID);
    return true;
}
bool CJCBase::Ans1064()
{

    QString strPD=QString(QLatin1String(m_sDataArea));
    QStringList list1 = strPD.split("=");
    if(list1.size()==2)
    {
        QString strA=list1.at(0);
        QString strB=list1.at(1);
        if(strA.compare("RtdInterval")==0)
            m_nFSBJG=strB.toInt();
    }

    QString strQQYD=SpellUpDataTable(QString(m_sQQBM),"9011",4,"QnRtn=1");//请求应答数据
    QByteArray  baSpell=SpellPackage(strQQYD); //拼接整个包
    TcpSendVal(baSpell.data(),baSpell.size(),m_nNetID);

    QString strZXJG=SpellUpDataTable(QString(m_sQQBM),"9012",4,"ExeRtn=1");//执行结果数据
    QByteArray  baSpell1=SpellPackage(strZXJG); //拼接整个包
    TcpSendVal(baSpell1.data(),baSpell1.size(),m_nNetID);
    return true;
}

bool CJCBase::Ans1072()
{

    QString strPD=QString(QLatin1String(m_sDataArea));
    QStringList list1 = strPD.split("=");
    if(list1.size()==2)
    {
        QString strA=list1.at(0);
        QString strB=list1.at(1);
        if(strA.compare("NewPW")==0)
        {
            QByteArray by=strB.toLatin1();
            char * sPW=by.data();
            strncpy((char *)&m_sFWMM[3],sPW,6);
        }
    }
    QString strQQYD=SpellUpDataTable(QString(m_sQQBM),"9011",4,"QnRtn=1");//请求应答数据
    QByteArray  baSpell=SpellPackage(strQQYD); //拼接整个包
    TcpSendVal(baSpell.data(),baSpell.size(),m_nNetID);

    QString strZXJG=SpellUpDataTable(QString(m_sQQBM),"9012",4,"ExeRtn=1");//执行结果数据
    QByteArray  baSpell1=SpellPackage(strZXJG); //拼接整个包
    TcpSendVal(baSpell1.data(),baSpell1.size(),m_nNetID);
    return true;
}
bool CJCBase::Ans2011()
{
    m_bSSSJ=true;

    QString strQQYD=SpellUpDataTable(QString(m_sQQBM),"9011",4,"QnRtn=1");//请求应答数据
    QByteArray  baSpell=SpellPackage(strQQYD); //拼接整个包
    TcpSendVal(baSpell.data(),baSpell.size(),m_nNetID);

    QString strZXJG=SpellUpDataTable(QString(m_sQQBM),"9012",4,"ExeRtn=1");//执行结果数据
    QByteArray  baSpell1=SpellPackage(strZXJG); //拼接整个包
    TcpSendVal(baSpell1.data(),baSpell1.size(),m_nNetID);
    return true;
}
bool CJCBase::Ans9014()
{
    QString str=QString(QLatin1String((char *)m_sQQBM));
    QStringList sl=str.split("=");
    sl.at(1);
    return true;
}
bool CJCBase::AiToCoding(stuCol& stu)
{
    //  QChar cID=stu.sCoding.at(2);
    int nID=CTool::chartoint(stu.sName[2]);
    if(nID==-1 || nID>=MNLJKSL_NUM)
    {
        COperationConfig::writelog(ERRORPROAINUM,(char *)stu.sName);
        return false;
    }
    strncpy(stu.sName,m_pMain->m_stuAIChan[nID].strJCX,6);
    if(strncmp(stu.sType,"Rtd",3)==0)
    {
        if(m_pMain->m_stuAIChan[nID].SignalType==0)//电流
        {stu.dvalue=m_pMain->m_stuAIChan[nID].nURV*((stu.dvalue-m_pMain->m_stuAIChan[nID].nLRV)/(20-4));}
        if(m_pMain->m_stuAIChan[nID].SignalType==1)//电压
        {stu.dvalue=m_pMain->m_stuAIChan[nID].nURV*((stu.dvalue-m_pMain->m_stuAIChan[nID].nLRV)/(10-0));}
    }


    return true;
}
bool CJCBase::SendComSet()
{
   // QString strSZD="CP=&&";
    QString strCom;
    //***************串口配置**********************
    for(int i=0;i<8;i++)
    {
        int nID=m_pMain->m_nCom[i];
        strCom+=QString::number(i+1)+",";
        int  nIsRun=(int)(m_pMain->m_stuChan[nID].isrun);
        strCom+=QString::number(nIsRun)+",";
        strCom+=QString(QLatin1String(m_pMain->m_stuChan[nID].strXY))+",";
    }
    //***************AI配置**********************
    for(int i=0;i<8;i++)
    {
       // int nID=m_pMain->m_nCom;
        strCom+=QString::number(i+21)+",";
        int  nIsRun=(int)(m_pMain->m_stuAIChan[i].bRun);
        strCom+=QString::number(nIsRun)+",";
        strCom+=QString::number(m_pMain->m_stuAIChan[i].SignalType)+",";
    }
    //**************************缺少开关量配置************************
    QString strLen=QString("%1").arg(strCom.size(), DATALENGTH, 10, QChar('0'));
    QString strSZD="CN=8000;CP=&&"+strCom+"&&";

    QByteArray baSZD=strSZD.toLatin1();
    int nCRC=CTool::CRC16_Checkout((unsigned char *)baSZD.data(),(unsigned int)baSZD.size());
    QString c=QString("%1").arg(nCRC, CRCLENGTH, 16, QChar('0')).toUpper();

    QString strSend="##"+strLen+strSZD+c+"\r\n";
    true;
}
