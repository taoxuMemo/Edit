#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formmain.h"
//#include "formreal.h"
#include "QMessageBox"
#include "QDateTime"
MainWindow::MainWindow(QWidget *parent) :
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

    m_pMyThread=new CMySocketThread(this);
    m_pNetConThread=new CNetConThread(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete  m_pMyThread;
    delete  m_pNetConThread;

    for(int i=0;i<6;i++)
    {
        if(m_pMySocket[i]!=NULL)
        {
            delete m_pMySocket[i];
            m_pMySocket[i]=NULL;
        }
    }
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
            return false;
        }

    }
    //获取网络配置信息
    for(int i=0;i<6;i++)
    {
        bool bb=m_pOpera->ReadIPAddr(&m_stuIPA[i],i+1);

        m_pMySocket[i]=new CMySocket();
        m_pMySocket[i]->SetParam(m_stuIPA[i]);
    }

    return true;

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
void MainWindow::timerEvent(QTimerEvent *event)
{
    //********************实时数据上报间隔******************************
    static int nMSB=0;
    if(m_DBSTJC.m_nMSBJG==nMSB)
    {
        if(m_DBSTJC.m_bSSSJ==true)
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





























s
