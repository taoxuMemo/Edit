#include "formhistory.h"
#include "ui_formhistory.h"
#include "mainwindow.h"
int  FormHistory::isNew=0;
FormHistory::FormHistory(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormHistory)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    FormHistory::isNew++;
}

FormHistory::~FormHistory()
{
    delete ui;
    FormHistory::isNew--;
}

void FormHistory::on_pushButton_main_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}

void FormHistory::on_pushButton_last_clicked()
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->close();
    m_Main->CreateMainBtn();
}
