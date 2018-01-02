#include "formsetting_adc.h"
#include "ui_formsetting_adc.h"
int  FormSetting_ADC::isNew=0;
FormSetting_ADC::FormSetting_ADC(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting_ADC)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    FormSetting_ADC::isNew++;
}

FormSetting_ADC::~FormSetting_ADC()
{
    delete ui;
    FormSetting_ADC::isNew--;
}
