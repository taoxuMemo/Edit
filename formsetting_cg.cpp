#include "formsetting_cg.h"
#include "ui_formsetting_cg.h"
int  FormSetting_CG::isNew=0;
FormSetting_CG::FormSetting_CG(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting_CG)
{
    ui->setupUi(this);
     m_Main=pMainWindow;
     FormSetting_CG::isNew++;
}

FormSetting_CG::~FormSetting_CG()
{
    delete ui;
    FormSetting_CG::isNew--;
}
