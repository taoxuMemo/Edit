#include "formsetting_ck.h"
#include "ui_formsetting_ck.h"
#include"mainwindow.h"
#include"qdatatype.h"
#include"QMessageBox"
int  FormSetting_CK::isNew=0;
FormSetting_CK::FormSetting_CK(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting_CK)
{
    ui->setupUi(this);
    m_Main=pMainWindow;

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
//*******************************com选项变更*********************************
void FormSetting_CK::on_comboBox_currentIndexChanged(int index)
{

    int nChn=m_Main->m_nCom[index];
    ui->comboBox_2->setCurrentIndex(nChn-1);

}
//*******************************chn选项变更*********************************
void FormSetting_CK::on_comboBox_2_currentIndexChanged(int index)
{
     //  QMessageBox::information(this,"123",QString::number(index));
    stuChannel stuChan=m_Main->m_stuChan[index];
    ui->comboBox_3->setCurrentText(QString::number(stuChan.nBaud));
    ui->comboBox_4->setCurrentText(QString::number(stuChan.nData));
    ui->comboBox_5->setCurrentText(QString::number(stuChan.nStop));
    ui->comboBox_6->setCurrentText(QString(stuChan.nParity));

    ui->checkBox_2->setChecked(stuChan.bMinAvg);
    ui->checkBox_3->setChecked(stuChan.bMinMax);
    ui->checkBox_4->setChecked(stuChan.bMinMin);
    ui->checkBox_5->setChecked(stuChan.bMinTotal);

    ui->checkBox_8->setChecked(stuChan.bHourAvg);
    ui->checkBox_6->setChecked(stuChan.bHourMax);
    ui->checkBox_9->setChecked(stuChan.bHourMin);
    ui->checkBox_7->setChecked(stuChan.bHourTotal);

    ui->checkBox_12->setChecked(stuChan.bDayAvg);
    ui->checkBox_10->setChecked(stuChan.bDayMax);
    ui->checkBox_13->setChecked(stuChan.bDayMin);
    ui->checkBox_11->setChecked(stuChan.bDayTotal);

    ui->spinBox->setValue(stuChan.nAlarmUp);
    ui->spinBox_2->setValue(stuChan.nAlarmDown);
    ui->spinBox_3->setValue(stuChan.nCycle);

  //  int dex =ui->comboBox_3->currentIndex();
  //  QMessageBox::information(this,"123",QString::number(dex));
   // stuChan.nBaud

}
//***********************保存按钮**********************************
void FormSetting_CK::on_pushButton_3_clicked()
{
    int dexcom=ui->comboBox->currentIndex();
//    char* cCom=g_pCom[dex];
//    cCom+=3;
//    int num=atoi(cCom);
    int dexchn=ui->comboBox_2->currentIndex();
    m_Main->m_nCom[dexcom]=dexchn+1;
    m_Main->m_stuChan[dexchn].isrun=ui->checkBox->isChecked();
    m_Main->m_stuChan[dexchn].nBaud=g_nBaud[ui->comboBox_3->currentIndex()];
    m_Main->m_stuChan[dexchn].nData=g_cData[ui->comboBox_4->currentIndex()];
    m_Main->m_stuChan[dexchn].nStop=g_fStop[ui->comboBox_5->currentIndex()];
    m_Main->m_stuChan[dexchn].nParity=g_cParity[ui->comboBox_6->currentIndex()];

    m_Main->m_stuChan[dexchn].bMinAvg=ui->checkBox_2->isChecked();
    m_Main->m_stuChan[dexchn].bMinMax=ui->checkBox_3->isChecked();
    m_Main->m_stuChan[dexchn].bMinMin=ui->checkBox_4->isChecked();
    m_Main->m_stuChan[dexchn].bMinTotal=ui->checkBox_5->isChecked();
    m_Main->m_stuChan[dexchn].bHourAvg=ui->checkBox_8->isChecked();
    m_Main->m_stuChan[dexchn].bHourMax=ui->checkBox_6->isChecked();
    m_Main->m_stuChan[dexchn].bHourMin=ui->checkBox_9->isChecked();
    m_Main->m_stuChan[dexchn].bHourTotal=ui->checkBox_7->isChecked();
    m_Main->m_stuChan[dexchn].bDayAvg=ui->checkBox_12->isChecked();
    m_Main->m_stuChan[dexchn].bDayMax=ui->checkBox_10->isChecked();
    m_Main->m_stuChan[dexchn].bDayMin=ui->checkBox_13->isChecked();
    m_Main->m_stuChan[dexchn].bDayTotal=ui->checkBox_11->isChecked();

    m_Main->m_stuChan[dexchn].nAlarmUp=ui->spinBox->value();
    m_Main->m_stuChan[dexchn].nAlarmDown=ui->spinBox_2->value();
    m_Main->m_stuChan[dexchn].nCycle=ui->spinBox_3->value();

      if(QMessageBox::information(this,"配置信息","是否确定修改配置信息",QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
          {
          m_Main->m_pOpera->WriteCom(dexcom+1,dexchn);
          m_Main->m_pOpera->writeChn(m_Main->m_stuChan[dexchn],dexchn);
      }
}


