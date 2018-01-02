#include "formsetting_yzsb.h"
#include "ui_formsetting_yzsb.h"
int  FormSetting_YZSB::isNew=0;
FormSetting_YZSB::FormSetting_YZSB(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting_YZSB)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    FormSetting_YZSB::isNew++;
}

FormSetting_YZSB::~FormSetting_YZSB()
{
    delete ui;
    FormSetting_YZSB::isNew--;
}
