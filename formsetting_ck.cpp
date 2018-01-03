#include "formsetting_ck.h"
#include "ui_formsetting_ck.h"
#include"QMainWindow"
#include"qdatatype.h"
#include"QMessageBox"
int  FormSetting_CK::isNew=0;
FormSetting_CK::FormSetting_CK(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting_CK)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
   // pMainWindow->
    FormSetting_CK::isNew++;
    int num; //元素的数量
    //*************************控件初始化*****************************************
    //初始化串口号

    for(int i=0;i<8;i++ ){

        ui->comboBox->addItem(QString(QLatin1String(g_pCom[i])));
        ui->comboBox_2->addItem(QString(QLatin1String(g_pChn[i])));
    }

//    //初始化通道号
//    //初始化波特率控件
    num=sizeof(g_nBaud)/sizeof(int);
    for(int i=0;i<num;i++)
    {
        QString str=QString::number(g_nBaud[i]);
        ui->comboBox_3->addItem(str);
    }
    //初始化数据位
    for(int i=0;i<4;i++)
    {
        QString str=QString::number(g_cData[i]);
        ui->comboBox_4->addItem(str);
    }
    //初始化停止位
    for(int i=0;i<3;i++)
    {
        QString str=QString::number(g_fStop[i]);
        ui->comboBox_5->addItem(str);
    }
    //初始化校验位
    for(int i=0;i<3;i++)
    {
        QString str=QChar(g_cParity[i]);//=QString::sprintf("%c",g_cParity[i]);
        //str.sprintf("%c",g_cParity[i])；
        ui->comboBox_6->addItem(str);
    }

}

FormSetting_CK::~FormSetting_CK()
{
    delete ui;
     FormSetting_CK::isNew--;

}

void FormSetting_CK::on_pushButton_last_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();

}

void FormSetting_CK::on_comboBox_currentIndexChanged(int index)
{
    QMessageBox::information(this,"123",QString::number(index));
}
