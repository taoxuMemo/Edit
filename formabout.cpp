#include "formabout.h"
#include "ui_formabout.h"
#include "mainwindow.h"
int  FormAbout::isNew=0;
FormAbout::FormAbout(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAbout)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    FormAbout::isNew++;
}

FormAbout::~FormAbout()
{
    delete ui;
    FormAbout::isNew--;
}

void FormAbout::on_pushButton_last_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();

}

void FormAbout::on_pushButton_main_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}
