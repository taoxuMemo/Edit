#include "formsetting_wlsz.h"
#include "ui_formsetting_wlsz.h"
#include"qdatatype.h"
#include"qmessagebox.h"
#include"coperationconfig.h"
//#include"qmainwindow.h"
#include"mainwindow.h"
int  FormSetting_WLSZ::isNew=0;
FormSetting_WLSZ::FormSetting_WLSZ(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting_WLSZ)
{
    ui->setupUi(this);
     m_Main=pMainWindow;
     FormSetting_WLSZ::isNew++;
     for(int i=0;i<6;i++)
     {
         ui->comboBox_ID->addItem(g_ipaddr[i]);
     }
}

FormSetting_WLSZ::~FormSetting_WLSZ()
{
    delete ui;
    FormSetting_WLSZ::isNew--;
}

void FormSetting_WLSZ::on_radioButton_YX_clicked(bool checked)
{
    ui->radioButton_WX->setChecked(!checked);
}

void FormSetting_WLSZ::on_radioButton_WX_clicked(bool checked)
{
     ui->radioButton_YX->setChecked(!checked);
}

void FormSetting_WLSZ::on_radioButton_TCP_clicked(bool checked)
{
    ui->radioButton_UDP->setChecked(!checked);
}

void FormSetting_WLSZ::on_radioButton_UDP_clicked(bool checked)
{
    ui->radioButton_TCP->setChecked(!checked);
}

void FormSetting_WLSZ::on_comboBox_ID_currentIndexChanged(int index)
{
    stuIPAddr stuip=m_Main->m_stuIPA[index];
    ui->checkBox_RUN->setChecked(stuip.bIsrun);
    ui->lineEdit_NAME->setText(QString(stuip.sName));
    ui->lineEdit_IP->setText(QString(stuip.sIP));
    ui->lineEdit_EX->setText(QString(stuip.sExtend));
    ui->lineEdit_PORT->setText(QString::number(stuip.nPort));
}

void FormSetting_WLSZ::on_pushButton_clicked()
{
    //********  **未加安全性判断******
    //******************远程IP 设置**********************************
    stuIPAddr stuaddr;
    bool bIsrun=ui->checkBox_RUN->checkState();
    int nIPID=ui->comboBox_ID->currentIndex();
    QString strName=ui->lineEdit_NAME->text();
    QString strIP=ui->lineEdit_IP->text();
    int nPort=ui->lineEdit_PORT->text().toInt();
    QString strEx=ui->lineEdit_EX->text();
    //**************本地IP 设置************************

    //************协议类型及传输方式********************
    bool bXY=ui->radioButton_TCP->isChecked();

    stuaddr.bIsrun=bIsrun;
    memcpy(stuaddr.sName,strName.toLatin1().data(),strName.length());
    stuaddr.sName[strName.length()]='\0';
    memcpy( stuaddr.sIP,strIP.toLatin1().data(),strIP.length());
    stuaddr.sIP[strIP.length()]='\0';
    stuaddr.nPort=nPort;
    memcpy( stuaddr.sExtend,strEx.toLatin1().data(),strEx.length());
    stuaddr.sExtend[strEx.length()]='\0';
    m_Main->m_stuIPA[nIPID]=stuaddr;
    m_Main->m_pOpera->WriteIPAddr(stuaddr,nIPID);




    if(QMessageBox::information(this,"网络配置","是否确定修改网络配置",QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
        {
        m_Main->m_pOpera->WriteIPAddr(stuaddr,nIPID);
    }



}
