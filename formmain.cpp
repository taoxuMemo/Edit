#include "formmain.h"
#include "ui_formmain.h"
#include"mainwindow.h"
FormMain::FormMain(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{
    m_Main=pMainWindow;
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
    setWindowState(Qt::WindowMaximized);
}

FormMain::~FormMain()
{
    delete ui;
}

void FormMain::on_pushButton_3_clicked()//进入实时数据页
{
    this->hide();
    m_Main->CreateRealTime();
}

void FormMain::on_pushButton_main_clicked()//返回主页
{
  //  this->hide();
  //  m_Main->CreateMainBtn();
}

void FormMain::on_pushButton_last_clicked() //返回上一页
{
 //   this->hide();
 //   m_Main->CreateMainBtn();
}

void FormMain::on_pushButton_history_clicked()//触发历史数据按钮
{
    this->hide();
    m_Main->CreateHistory();
}

void FormMain::on_pushButton_analysis_clicked()//触发数据分析按钮
{
    this->hide();
    m_Main->CreateAnalysis();
}

void FormMain::on_pushButton_online_clicked()//触发在线诊断按钮
{
    this->hide();
    m_Main->CreateOnline();
}

void FormMain::on_pushButton_query_clicked()//触发日志查询按钮
{
    this->hide();
    m_Main->CreateQuery();
}

void FormMain::on_pushButton_state_clicked()//触发在线状态按钮
{
    this->hide();
    m_Main->CreateState();
}

void FormMain::on_pushButton_setting_clicked()//触发系统设置按钮
{
    this->hide();
    m_Main->CreateSetting();
}

void FormMain::on_pushButton_about_clicked()//触发关于我们按钮
{
    this->hide();
     m_Main->CreateAbout();
}

void FormMain::on_pushButton_clicked()
{
  //  m_Main->m_thdTest= new CTestTcpThd()
    m_Main->m_pthdTest->MyListen();
}
