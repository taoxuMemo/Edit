#include "formstate.h"
#include "ui_formstate.h"
#include "mainwindow.h"
int  FormState::isNew=0;
FormState::FormState(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormState)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    FormState::isNew++;
}

FormState::~FormState()
{
    delete ui;
    FormState::isNew--;
}

void FormState::on_pushButton_main_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}

void FormState::on_pushButton_last_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}
