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
//   QString strNum=str.mid(3,1);
//   int num=strNum.toInt();
//   if(num>8 || num<1)
//       {
//       COperationConfig::writelog(CONFIGCOMVOER,QString::number(num).toLatin1().data());
//       return 0;
//   }
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
bool COperationConfig::WriteCom(int num)
{}
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


}
bool COperationConfig::writeChn(stuChannel chn)
{}

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
