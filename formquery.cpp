#include "formquery.h"
#include "ui_formquery.h"
#include "mainwindow.h"
int  FormQuery::isNew=0;
FormQuery::FormQuery(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormQuery)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    FormQuery::isNew++;
}

FormQuery::~FormQuery()
{
    delete ui;
    FormQuery::isNew--;
}

void FormQuery::on_pushButton_main_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}

void FormQuery::on_pushButton_last_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}
