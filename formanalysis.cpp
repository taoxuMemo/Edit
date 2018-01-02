#include "formanalysis.h"
#include "ui_formanalysis.h"
#include "mainwindow.h"
int  FormAnalysis::isNew=0;
FormAnalysis::FormAnalysis(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAnalysis)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    FormAnalysis::isNew++;
}

FormAnalysis::~FormAnalysis()
{
    delete ui;
    FormAnalysis::isNew--;
}

void FormAnalysis::on_pushButton_main_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}

void FormAnalysis::on_pushButton_last_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}
