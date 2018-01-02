#include "formsetting_wlsz.h"
#include "ui_formsetting_wlsz.h"
int  FormSetting_WLSZ::isNew=0;
FormSetting_WLSZ::FormSetting_WLSZ(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting_WLSZ)
{
    ui->setupUi(this);
     m_Main=pMainWindow;
     FormSetting_WLSZ::isNew++;
}

FormSetting_WLSZ::~FormSetting_WLSZ()
{
    delete ui;
    FormSetting_WLSZ::isNew--;
}
