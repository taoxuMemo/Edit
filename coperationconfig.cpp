#include "coperationconfig.h"
#include"QFile"
#include "QDateTime"
#include"QMessageBox"
COperationConfig::COperationConfig()
{
    m_file=nullptr;
//*************判断配置文件数否存在**************************
    QFile file(m_sFileName);
    m_bTag=file.exists();
    if(!m_bTag)
    {
        COperationConfig::writelog(CONFIGOPENERR);
        return;
    }else
        {

        m_file=new QSettings(m_sFileName, QSettings::IniFormat);

    }
//******************************************************
}
COperationConfig::~COperationConfig()
{
    if(m_file!=nullptr)
        delete m_file;
}
bool COperationConfig::ReadIPAddr(stuIPAddr *stu,int num)
{
    if(!m_bTag)
        return 0;
     QString Sec="/addr"+QString::number(num);
     stu->bIsrun= m_file->value(Sec+"/isrun").toInt();
     QString strname= m_file->value(Sec+"/name").toString();
     int nName=strname.length();
     if(nName>20)
     {
         COperationConfig::writelog(CONFIGIPNAMELEN,QString::number(num).toLatin1().data()) ;
         return false;
     }
     memcpy(stu->sName,strname.toLatin1().data(),nName);
     stu->sName[nName]='\0';
     QString strIP=m_file->value(Sec+"/ip").toString();
     int nIP=strIP.length();
     if(nIP>19)
     {
         COperationConfig::writelog(CONFIGIPIPADDRLEN,QString::number(num).toLatin1().data()) ;
         return false;
     }
     memcpy(stu->sIP,strIP.toLatin1().data(),nIP);
     stu->sIP[nIP]='\0';

     stu->nPort= m_file->value(Sec+"/port").toInt();

     QString strextend= m_file->value(Sec+"/extend").toString();
     int nExtend=strname.length();
     if(nExtend>19)
     {
         COperationConfig::writelog(CONFIGIPEXTENDLEN,QString::number(num).toLatin1().data()) ;
         return false;
     }
     memcpy(stu->sExtend,strextend.toLatin1().data(),nExtend);
     stu->sExtend[nExtend]='\0';
     stu->isChange=true;
     return true;
}

bool COperationConfig::WriteIPAddr(stuIPAddr stu, int num)
{
    if(!m_bTag)
        return 0;
    QString Sec="/chn"+QString::number(num+1);

    m_file->setValue(Sec+"/isrun",QString::number(stu.bIsrun));
    m_file->setValue(Sec+"/name",QString(stu.sName));
    m_file->setValue(Sec+"/ip",QString(stu.sIP));
    m_file->setValue(Sec+"/port",QString::number(stu.nPort));
    m_file->setValue(Sec+"/extend",QString(stu.sExtend));
    return true;
}
int COperationConfig::ReadCom(int num)
{
    if(!m_bTag)
        return 0;
   QString stttt="/com/com"+QString::number(num);
   QString str= m_file->value(stttt).toString();
   if(str.length()!=4)//判断长度是否正确
       {
       COperationConfig::writelog(CONFIGCOMLEN,QString::number(num).toLatin1().data());
       return 0;
   }

      char *pStr=str.toLatin1().data();
      pStr+=3;
      char cStr=*pStr;
      if(cStr<'1' || cStr>'8')
      {
           COperationConfig::writelog(CONFIGCOMVOER,QString::number(num).toLatin1().data());
           return 0;
      }
      int renum=atoi(pStr);
      return renum;

}
bool COperationConfig::WriteCom(int nCom,int nChn)
{
    if(!m_bTag)
        return 0;
    QString stttt="/com/com"+QString::number(nCom);
    m_file->setValue(stttt,g_pChn[nChn]);
    return true;

}
bool COperationConfig::ReadChn(stuChannel * stu,int num)
{
    if(!m_bTag)
        return 0;
    //判断stu是否被new

   QString Sec="/chn"+QString::number(num);
   //**********************************提取isrun********************************************88
   QString strisrun= m_file->value(Sec+"/isrun").toString();
   char cc=*(strisrun.toLatin1().data());
   if(cc=='1')
       stu->isrun=1;
   else if(cc=='0')
       stu->isrun=0;
   else
       {
       COperationConfig::writelog(CONFIGISRUN,QString::number(num).toLatin1().data());
       return false;
   }
    //*****************************提取波特率************************************************
   bool bBuad=false;
   QString strbaud= m_file->value(Sec+"/baud").toString();
   for(int i=0;i<8;i++)
       {
       QString strB=QString::number(g_nBaud[i]);
       if(QString::compare(strB,strbaud)==0)
           {
           stu->nBaud=g_nBaud[i];
           bBuad=true;
           break;
       }
   }
   if(!bBuad)
       {
       COperationConfig::writelog(CONFIGBUAD,QString::number(num).toLatin1().data());
       return false;
   }
   //*************************************提取数据位**************************************************
   bool bData=false;
   QString strdata= m_file->value(Sec+"/data").toString();
   for(int i=0;i<4;i++)
       {
       QString strDa=QString::number(g_cData[i]);
       if(QString::compare(strdata,strDa)==0)
           {
           stu->nData=g_cData[i];
           bData=true;
           break;
       }
   }
   if(!bData)
       {
       COperationConfig::writelog(CONFIGDATA,QString::number(num).toLatin1().data());
       return false;
   }
   //*****************************************提取停止位*********************************
   bool bStop=false;
   QString strstop= m_file->value(Sec+"/stop").toString();
   for(int i=0;i<3;i++)
       {
       QString strSt=QString::number(g_fStop[i]);
       if(QString::compare(strstop,strSt)==0)
           {
           stu->nData=g_fStop[i];
           bStop=true;
           break;
       }
   }
   if(!bStop)
       {
       COperationConfig::writelog(CONFIGSTOP,QString::number(num).toLatin1().data());
       return false;
   }
  //*****************************************提取校验位*********************************
    bool bParity=false;
    QString strparity= m_file->value(Sec+"/parity").toString();
    for(int i=0;i<3;i++)
        {
        char cPa=*(strparity.toLatin1().data());
        if(cPa==g_cParity[i])
            {
            stu->nParity=g_cParity[i];
            bParity=true;
            break;
        }
    }
    if(!bParity)
        {
        COperationConfig::writelog(CONFIGPARITY,QString::number(num).toLatin1().data());
        return false;
    }
//*********************************取checkbox分小时天********************************
     QString strMinAvg= m_file->value(Sec+"/favg").toString();
     if(!CheckBool(strMinAvg))
     {
         COperationConfig::writelog(CONFIGCHNMINAVG,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bMinAvg=strMinAvg.toInt();

     QString strMinMax= m_file->value(Sec+"/fmax").toString();
     if(!CheckBool(strMinMax))
     {
         COperationConfig::writelog(CONFIGCHNMINMAX,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bMinMax=strMinMax.toInt();

     QString strMinMin= m_file->value(Sec+"/fmin").toString();
     if(!CheckBool(strMinMin))
     {
         COperationConfig::writelog(CONFIGCHNMINMIN,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bMinMin=strMinMin.toInt();

     QString strMinTotal= m_file->value(Sec+"/ftotal").toString();
     if(!CheckBool(strMinTotal))
     {
         COperationConfig::writelog(CONFIGCHNMINTOTAL,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bMinTotal=strMinTotal.toInt();
     //*************************************小时***************************************
     QString strHourAvg= m_file->value(Sec+"/xavg").toString();
     if(!CheckBool(strHourAvg))
     {
         COperationConfig::writelog(CONFIGCHNHOURAVG,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bHourAvg=strHourAvg.toInt();

     QString strHourMax= m_file->value(Sec+"/xmax").toString();
     if(!CheckBool(strHourMax))
     {
         COperationConfig::writelog(CONFIGCHNHOURMAX,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bHourMax=strHourMax.toInt();

     QString strHourMin= m_file->value(Sec+"/xmin").toString();
     if(!CheckBool(strHourMin))
     {
         COperationConfig::writelog(CONFIGCHNHOURMIN,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bHourMin=strHourMin.toInt();

     QString strHourTotal= m_file->value(Sec+"/xtotal").toString();
     if(!CheckBool(strHourTotal))
     {
         COperationConfig::writelog(CONFIGCHNHOURTOTAL,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bHourTotal=strHourTotal.toInt();
     //***************************************天*************************************
     QString strDayAvg= m_file->value(Sec+"/ravg").toString();
     if(!CheckBool(strDayAvg))
     {
         COperationConfig::writelog(CONFIGCHNDAYAVG,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bDayAvg=strDayAvg.toInt();

     QString strDayMax= m_file->value(Sec+"/rmax").toString();
     if(!CheckBool(strDayMax))
     {
         COperationConfig::writelog(CONFIGCHNDAYMAX,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bDayMax=strDayMax.toInt();

     QString strDayMin= m_file->value(Sec+"/rmin").toString();
     if(!CheckBool(strDayMin))
     {
         COperationConfig::writelog(CONFIGCHNDAYMIN,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bDayMin=strDayMin.toInt();

     QString strDayTotal= m_file->value(Sec+"/rtotal").toString();
     if(!CheckBool(strDayTotal))
     {
         COperationConfig::writelog(CONFIGCHNDAYTOTAL,QString::number(num).toLatin1().data());
         return false;
     }
     stu->bDayTotal=strDayTotal.toInt();

     //***************************************报警值******************************************
     stu->nAlarmUp=m_file->value(Sec+"/upper").toInt();
     stu->nAlarmDown=m_file->value(Sec+"/lower").toInt();
     stu->nCycle=m_file->value(Sec+"/cycle").toInt();
     return true;



}
//***************判断是否为bool型*********************************
bool COperationConfig::CheckBool(QString str)
{
    if(str.length()!=1)
        return false;
    char s=*(str.toLatin1().data());
    if(s!='1' && s!='0')
        return false;
    return true;
}
bool COperationConfig::writeChn(stuChannel chn,int num)
{
    if(!m_bTag)
        return 0;
    //判断stu是否被new

   QString Sec="/chn"+QString::number(num+1);

   m_file->setValue(Sec+"/isrun",QString::number(chn.isrun));
   m_file->setValue(Sec+"/baud",QString::number(chn.nBaud));
   m_file->setValue(Sec+"/data",QString::number(chn.nData));
   m_file->setValue(Sec+"/stop",QString::number(chn.nStop));
   m_file->setValue(Sec+"/parity",QString(chn.nParity));

   m_file->setValue(Sec+"/favg",QString::number(chn.bMinAvg));
   m_file->setValue(Sec+"/fmin",QString::number(chn.bMinMin));
   m_file->setValue(Sec+"/fmax",QString::number(chn.bMinMax));
   m_file->setValue(Sec+"/ftotal",QString::number(chn.bMinTotal));

   m_file->setValue(Sec+"/xavg",QString::number(chn.bHourAvg));
   m_file->setValue(Sec+"/xmin",QString::number(chn.bHourMin));
   m_file->setValue(Sec+"/xmax",QString::number(chn.bHourMax));
   m_file->setValue(Sec+"/xtotal",QString::number(chn.bHourTotal));

   m_file->setValue(Sec+"/ravg",QString::number(chn.bDayAvg));
   m_file->setValue(Sec+"/rmin",QString::number(chn.bDayMin));
   m_file->setValue(Sec+"/rmax",QString::number(chn.bDayMax));
   m_file->setValue(Sec+"/rtotal",QString::number(chn.bDayTotal));

   m_file->setValue(Sec+"/upper",QString::number(chn.nAlarmUp));
   m_file->setValue(Sec+"/lower",QString::number(chn.nAlarmDown));
   m_file->setValue(Sec+"/cycle",QString::number(chn.nCycle));
    return true;
}

//********************************静态成员变量用于写入日志文件**************************************
void COperationConfig::writelog(int nErr, char *sRemark)
{
    try{
     QString strName="./log"+QDateTime::currentDateTime().toString("yyyy-MM-dd");
     QFile file(strName);
     file.open(QIODevice::WriteOnly|QIODevice::Append);
     QString serr = QString("%1").arg(nErr, 8, 16, QLatin1Char('0'));
     QString strData=serr+"---"+QDateTime::currentDateTime().toString("hh:mm:ss")+"---"+QString(QLatin1String(sRemark))+"\n";
     file.write(strData.toLatin1().data());
     file.close();
     }
     catch(QString ex)
     {
      //  QMessageBox::information(this,"writelog异常信息",ex);
     }
}
