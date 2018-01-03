#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formmain.h"
//#include "formreal.h"
#include "QMessageBox"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //statusBar()->hide();

  //  setWindowFlags(Qt::FramelessWindowHint);
    init();//初始化配置文件及数据库
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
    //***************************end**********************************
    m_fm=new FormMain(this,ui->widget);
    m_fm->show();
    m_nTest=56;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init()
{
    m_pOpera=new COperationConfig();
    if(m_pOpera->m_bTag==false)
     {
        this->close();
        return;
     }
    for(int i=0;i<8;i++)
        {
       m_nCom[i]= m_pOpera->ReadCom(i+1);
       bool bb=m_pOpera->ReadChn(&m_stuChan[i],i+1);

    }

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
    QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
