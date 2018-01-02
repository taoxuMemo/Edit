#include "formsetting_sjjy.h"
#include "ui_formsetting_sjjy.h"
#include "QDateTime"
#include "QDate"
#include "QTime"
int  FormSetting_SJJY::isNew=0;
FormSetting_SJJY::FormSetting_SJJY(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting_SJJY)
{
    ui->setupUi(this);
     m_Main=pMainWindow;
     FormSetting_SJJY::isNew++;
}

FormSetting_SJJY::~FormSetting_SJJY()
{
    delete ui;
    FormSetting_SJJY::isNew--;
}

void FormSetting_SJJY::on_spinBox_valueChanged(int arg1)
{
    if(arg1>2035)
        ui->spinBox->setValue(2000);
    if(arg1<2000)
        ui->spinBox->setValue(2035);
  //  if(a>2030)

}

void FormSetting_SJJY::on_pushButton_clicked()
{
    QTime time=QDateTime::currentDateTime().time();

    QDate date=QDateTime::currentDateTime().date();

    ui->spinBox->setValue(date.year());
    ui->spinBox_2->setValue(date.month());
    ui->spinBox_3->setValue(date.day());
    ui->spinBox_4->setValue(time.hour());
    ui->spinBox_5->setValue(time.minute());
    ui->spinBox_6->setValue(time.second());

}

void FormSetting_SJJY::on_pushButton_2_clicked()
{
    QString  year= QString::number(ui->spinBox->value());
    QString  month=QString::number(ui->spinBox_2->value());
    QString  day=QString::number(ui->spinBox_3->value());
    QString  hour=QString::number(ui->spinBox_4->value());
    QString  min=QString::number(ui->spinBox_5->value());
    QString  sec=QString::number(ui->spinBox_6->value());
    QString  strdate =  "date -s " + month + "/" + day + "/" + year;
    system(strdate.toLatin1().data());
    QString  strtime = "date -s " + hour + ":" + min + ":" + sec;
    system(strtime.toLatin1().data());
        //强制写入到CMOS
    system("clock -w");
}
