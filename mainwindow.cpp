#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formmain.h"
//#include "formreal.h"
#include "QMessageBox"
#include "QDateTime"
MainWindow::        MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //statusBar()->hide();
    m_bRun=true;
    //    //  setWindowFlags(Qt::FramelessWindowHint);
    //    m_bRun=init();//初始化配置文件及数据库
    //    if(!m_bRun)
    //        return;
    //*****************************************************
    m_model=new  QStringListModel();
    ui->listView_MSG->setModel(m_model);
    // connect(m_pMyThread, SIGNAL(TestSignal(QString)), this, SLOT(DisplayMsg(QString)));
    //  connect(m_pNetConThread, SIGNAL(TestSignal(QString)), this, SLOT(DisplayMsg(QString)));
    connect(this, SIGNAL(RecvSignal(QByteArray)), this, SLOT(RecvMsg(QByteArray))); //单片解数据接收巢
    connect(this, SIGNAL(RecvTcpSignal(QByteArray,int)), this, SLOT(RecvTcpMsg(QByteArray,int))); //单片解数据接收巢
    init();
    //**********************初始化窗体指针***********************************
    m_fm=NULL;
    m_fr=NULL;
    m_fabout=NULL;
    m_fanalysis=NULL;
    m_fhistory=NULL;
    m_fonline=NULL;
    m_fquery=NULL;
    m_fsetting=NULL;
    m_fstate=NULL;
    m_fsetting_ck=NULL;
    m_fsetting_sjjy=NULL;
    m_fsetting_wlsz=NULL;
    //***************************end**********************************
    m_fm=new FormMain(this,ui->widget);
    m_fm->show();
    m_nTest=56;



    //****************
    switch(m_nColType)
    {
    case 31:
        m_pBase=new CQJCYZ(this);
        break;
    case 32:
        m_pBase=new CDBSTJC(this);
        break;
    default:

        break;
    }

    m_pBase->init();
    m_pthdTest=new CTestTcpThd(this);
    //启动串口采集线程
    m_pMyThread=new CMySocketThread(this);
    m_pMyThread->start();
    m_pNetConThread=new CNetConThread(this);
    m_pNetConThread->start();
    m_pSerialThread =new CSerialThread(this);//创建串口采集线程
    m_pRs232=new CRs232(this);
    if(m_pRs232->start()==false)
    {
        COperationConfig::writelog(SYSSTARTCONSERIALERROR);
    }
    //
    //    m_pSerialThread->SetParam("/dev/ttyO2",9600);
    //    m_pSerialThread->start();
}

MainWindow::~MainWindow()
{

    m_pMyThread->stop();
    while(m_pMyThread->isRunning());

    m_pNetConThread->stop();
    while(m_pNetConThread->isRunning());

    for(int i=0;i<6;i++)
    {
        if(m_pMySocket[i]!=NULL)
        {
            delete m_pMySocket[i];
            m_pMySocket[i]=NULL;
        }
    }
    delete ui;
}
bool MainWindow::init()
{
    m_pOpera=new COperationConfig();
    if(m_pOpera->m_bTag==false)
    {
        //  this->close();
        return false;
    }
    //获取串口通道信息
    for(int i=0;i<8;i++)
    {
        m_nCom[i]= m_pOpera->ReadCom(i+1);
        bool bb=m_pOpera->ReadChn(&m_stuChan[i],i+1);
        if(bb==false)
        {
            // QMessageBox::information(this,"异常信息","程序异常关闭 请查看错误日志！！！！");
            COperationConfig::writelog(CONFIGCOMERROT,QString::number(i).toLatin1().data());
            return false;
        }

    }
    //获取模拟量配置信息
    for(int i=0;i<MNLJKSL_NUM;i++)
    {
        m_pOpera->ReadAI(&m_stuAIChan[i],i+1);
    }

    //获取网络配置信息
    for(int i=0;i<6;i++)
    {
        m_pOpera->ReadIPAddr(&m_stuIPA[i],i+1);

        m_pMySocket[i]=new CMySocket();
        m_pMySocket[i]->SetParam(m_stuIPA[i]);
    }
    //获取设备标识和访问密码
    //memset(m_sSBWYBS,0,sizeof(m_sSBWYBS));
    //memset(m_sPassWD,0,sizeof(m_sPassWD));
    QString strType=m_pOpera->getText("col","type");
    m_nColType=strType.toInt();
    if(m_nColType!=31 && m_nColType!=32)
    {
        COperationConfig::writelog(CONFIGTYPEERROR);
        return false;
    }

    m_sPassWD=m_pOpera->getText("col","passwd");
    if(m_sPassWD.length()!=6)
    {
        COperationConfig::writelog(CONFIGPASSWORD);
        return false;
    }
    m_sSBWYBS=m_pOpera->getText("col","sysid");
    if(m_sSBWYBS.length()!=24)
    {
        COperationConfig::writelog(CONFIGEQUIPMENTID);
        return false;
    }
    //    QString str=m_pOpera->getText("col1","sysid2");
    if(m_mySql.init()==false)
    {
        COperationConfig::writelog(CONFIGEQUIPMENTID);
        return false;
    }
    return true;

}
void MainWindow::RecvData(QByteArray baData)
{
    emit RecvSignal(baData);
}
void MainWindow::RecvTcpData(QByteArray baData,int nID)
{
    emit RecvTcpSignal(baData,nID);
}
void MainWindow::RecvMsg(QByteArray baData)
{
    m_pBase->SerialInterFaceNew(baData.data(),baData.size(),0);
}
void MainWindow::RecvTcpMsg(QByteArray baData,int nID)
{
    m_pBase->NetInterFace(baData.data(),baData.size(),nID);
}
//***************************显示界面函数******************************
void MainWindow::CreateMainBtn()
{
    m_fm->show();
}
void MainWindow::CreateRealTime()
{

    if(FormReal::isNew!=0)
    {
        m_fr->show();
    }else {
        m_fr=new FormReal(this,ui->widget);
        m_fr->show();
    }
}
void MainWindow::CreateAbout()
{
    if(FormAbout::isNew!=0)
    {
        m_fabout->show();
    }else {
        m_fabout=new FormAbout(this,ui->widget);
        m_fabout->show();
    }
}

void MainWindow::CreateAnalysis()
{
    if(FormAnalysis::isNew!=0)
    {
        m_fanalysis->show();
    }else {
        m_fanalysis=new FormAnalysis(this,ui->widget);
        m_fanalysis->show();
    }
}
void MainWindow::CreateHistory()
{
    if(FormHistory::isNew!=0)
    {
        m_fhistory->show();
    }else {
        m_fhistory=new FormHistory(this,ui->widget);
        m_fhistory->show();
    }
}
void MainWindow::CreateOnline()
{
    if(FormOnline::isNew!=0)
    {
        m_fonline->show();
    }else {
        m_fonline=new FormOnline(this,ui->widget);
        m_fonline->show();
    }
}
void MainWindow::CreateQuery()
{
    if(FormQuery::isNew!=0)
    {
        m_fquery->show();
    }else {
        m_fquery=new FormQuery(this,ui->widget);
        m_fquery->show();
    }
}
void MainWindow::CreateSetting()
{
    if(FormSetting::isNew!=0)
    {
        m_fsetting->show();
    }else {
        m_fsetting=new FormSetting(this,ui->widget);
        m_fsetting->show();
    }
}
void MainWindow::CreateState()
{
    if(FormState::isNew!=0)
    {
        m_fstate->show();
    }else {
        m_fstate=new FormState(this,ui->widget);
        m_fstate->show();
    }
}
void MainWindow::CreateSetting_wlsz()
{
    if(FormSetting_WLSZ::isNew!=0)
    {
        m_fsetting_wlsz->show();
    }else {
        m_fsetting_wlsz=new FormSetting_WLSZ(this,ui->widget);
        m_fsetting_wlsz->show();
    }
}
void MainWindow::CreateSetting_ck()
{
    if(FormSetting_CK::isNew!=0)
    {
        m_fsetting_ck->show();
    }else {
        m_fsetting_ck=new FormSetting_CK(this,ui->widget);
        m_fsetting_ck->show();
    }
}
void MainWindow::CreateSetting_sjjy()
{
    if(FormSetting_SJJY::isNew!=0)
    {
        m_fsetting_sjjy->show();
    }else {
        m_fsetting_sjjy=new FormSetting_SJJY(this,ui->widget);
        m_fsetting_sjjy->show();
    }
}
//**********************************************************************
void MainWindow::on_pushButton_clicked()
{
    //   MainWindow  *pp= (MainWindow*)ui->
    //   int aaa=pp->m_nTest;
    //  QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    QApplication::exit(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(m_bRun)
    {

        ui->pushButton_2->setText("停止");
        m_bRun=!m_bRun;
        m_pNetConThread->start();
        m_pMyThread->start();
    }
    else
    {
        ui->pushButton_2->setText("启动");
        m_bRun=!m_bRun;
        m_pNetConThread->stop();
        m_pMyThread->stop();
    }
    //启动网络连接

}
void MainWindow::DisplayMsg(QString msg)
{


    QString str=msg+"-----"+QDateTime::currentDateTime().toString("hh:mm:ss");
    QStringList num =m_model->stringList();

    num<<str;
    m_model->setStringList(num);
    // ui->listView->model();


}
void MainWindow::SerialData(QString msg)
{
    return;
}
void MainWindow::timerEvent(QTimerEvent *event)
{
    //********************实时数据上报间隔******************************
    static int nMSB=0;
    if(m_pBase->m_nMSBJG==nMSB)
    {
        if(m_pBase->m_bSSSJ==true)
        {
            //
        }
        nMSB=0;
    }
    nMSB++;
    //分钟数据上报间隔

    //小时数据上报间隔
    //日数据上报间隔
}


void MainWindow::on_pushButton_3_clicked()
{
    QString str=ui->textEdit->toPlainText();
    char sData[1024];
    strncpy((char *)sData,str.toLatin1().data(),str.size());
    sData[str.size()]=0x0D;
    sData[str.size()+1]=0x0A;
    sData[str.size()+2]=0x00;
    m_pBase->SerialInterFaceNew((char *)sData,str.size()+2,0);
}

void MainWindow::AddRD(int nLen, int nFX)
{
    if(m_fr==NULL)
        return;
    m_fr->addlist(nLen,nFX);
}
void MainWindow::CheckChange()
{
    QString strVal=m_pOpera->getText("ischange","val");
    for(int i=0;i<strVal.size();i++)
    {
        stuIPAddr       stuIP;
        stuChannel      stuChn;
        stuYZSBSZ       stuItem;
        QChar cVal = strVal.at(i);
        if(cVal.toLatin1()=='1')
        {
            switch (i) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                m_pOpera->ReadIPAddr(&stuIP,1);
                m_pMySocket[0]->SetParam(stuIP);
                break;
            case 3:
                m_pOpera->ReadIPAddr(&stuIP,2);
                m_pMySocket[1]->SetParam(stuIP);
                break;
            case 4:
                m_pOpera->ReadIPAddr(&stuIP,3);
                m_pMySocket[2]->SetParam(stuIP);
                break;
            case 5:
                m_pOpera->ReadIPAddr(&stuIP,4);
                m_pMySocket[3]->SetParam(stuIP);
                break;
            case 6:
                m_pOpera->ReadIPAddr(&stuIP,5);
                m_pMySocket[4]->SetParam(stuIP);
                break;
            case 7:
                m_pOpera->ReadIPAddr(&stuIP,6);
                m_pMySocket[5]->SetParam(stuIP);
                break;
            case 8:
                m_pOpera->ReadChn(&stuChn,1);
                m_stuChan[0]=stuChn;
                break;
            case 9:
                m_pOpera->ReadChn(&stuChn,2);
                m_stuChan[1]=stuChn;
                break;
            case 10:
                m_pOpera->ReadChn(&stuChn,3);
                m_stuChan[2]=stuChn;
                break;
            case 11:
                m_pOpera->ReadChn(&stuChn,4);
                m_stuChan[3]=stuChn;
                break;
            case 12:
                m_pOpera->ReadChn(&stuChn,5);
                m_stuChan[4]=stuChn;
                break;
            case 13:
                m_pOpera->ReadChn(&stuChn,6);
                m_stuChan[5]=stuChn;
                break;
            case 14:
                m_pOpera->ReadChn(&stuChn,7);
                m_stuChan[6]=stuChn;
                break;
            case 15:
                m_pOpera->ReadChn(&stuChn,8);
                m_stuChan[7]=stuChn;
                break;
            case 16:
                m_pOpera->ReadItem(&stuItem,1);
                m_pBase->m_stuSJCYZBMB[0].stuYZ=stuItem;
                break;
            case 17:
                m_pOpera->ReadItem(&stuItem,2);
                m_pBase->m_stuSJCYZBMB[1].stuYZ=stuItem;
                break;
            case 18:
                m_pOpera->ReadItem(&stuItem,3);
                m_pBase->m_stuSJCYZBMB[2].stuYZ=stuItem;
                break;
            case 19:
                m_pOpera->ReadItem(&stuItem,4);
                m_pBase->m_stuSJCYZBMB[3].stuYZ=stuItem;
                break;
            case 20:
                m_pOpera->ReadItem(&stuItem,5);
                m_pBase->m_stuSJCYZBMB[4].stuYZ=stuItem;
                break;
            case 21:
                m_pOpera->ReadItem(&stuItem,6);
                m_pBase->m_stuSJCYZBMB[5].stuYZ=stuItem;
                break;
            case 22:
                m_pOpera->ReadItem(&stuItem,7);
                m_pBase->m_stuSJCYZBMB[6].stuYZ=stuItem;
                break;
            case 23:
                m_pOpera->ReadItem(&stuItem,8);
                m_pBase->m_stuSJCYZBMB[7].stuYZ=stuItem;
                break;
            case 24:
                m_pOpera->ReadItem(&stuItem,9);
                m_pBase->m_stuSJCYZBMB[8].stuYZ=stuItem;
                break;
            case 25:
                m_pOpera->ReadItem(&stuItem,10);
                m_pBase->m_stuSJCYZBMB[9].stuYZ=stuItem;
                break;
            case 26:
                m_pOpera->ReadItem(&stuItem,11);
                m_pBase->m_stuSJCYZBMB[10].stuYZ=stuItem;
                break;
            case 27:
                m_pOpera->ReadItem(&stuItem,12);
                m_pBase->m_stuSJCYZBMB[11].stuYZ=stuItem;
                break;
            default:
                break;
            }
        }
    }
    m_pOpera->writeText("ischange","val","0");
    return;
}
