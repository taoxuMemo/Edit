#include "formsetting_wlsz.h"
#include "ui_formsetting_wlsz.h"
#include"qdatatype.h"
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

}
