#include "formsetting_sb.h"
#include "ui_formsetting_sb.h"
int  FormSetting_SB::isNew=0;
FormSetting_SB::FormSetting_SB(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting_SB)
{
    ui->setupUi(this);
     m_Main=pMainWindow;
     FormSetting_SB::isNew++;
}

FormSetting_SB::~FormSetting_SB()
{
    delete ui;
    FormSetting_SB::isNew--;
}
