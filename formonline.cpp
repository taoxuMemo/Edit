#include "formonline.h"
#include "ui_formonline.h"
#include "mainwindow.h"
int  FormOnline::isNew=0;
FormOnline::FormOnline(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormOnline)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    FormOnline::isNew++;
}

FormOnline::~FormOnline()
{
    delete ui;
    FormOnline::isNew--;
}

void FormOnline::on_pushButton_main_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}

void FormOnline::on_pushButton_last_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}
