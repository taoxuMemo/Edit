#include "formsetting.h"
#include "ui_formsetting.h"
#include "mainwindow.h"
int  FormSetting::isNew=0;
FormSetting::FormSetting(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    FormSetting::isNew++;
}

FormSetting::~FormSetting()
{
    delete ui;
    FormSetting::isNew--;
}

void FormSetting::on_pushButton_main_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}

void FormSetting::on_pushButton_last_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}

void FormSetting::on_pushButton_5_clicked()//串口设置按钮
{
    this->hide();
    m_Main->CreateSetting_ck();
}

void FormSetting::on_pushButton_8_clicked()//时间设置按钮
{
    this->hide();
    m_Main->CreateSetting_sjjy();
}
//***************************************网络设置按钮触发函数******************************************************8
void FormSetting::on_pushButton_7_clicked()
{
    this->hide();
    m_Main->CreateSetting_wlsz();
}
