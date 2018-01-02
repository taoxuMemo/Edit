#include "formreal.h"
#include "ui_formreal.h"
#include"QStandardItem"
#include"QTableView"
#include"mainwindow.h"
int FormReal::isNew=0;
FormReal::FormReal(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormReal)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    QStandardItemModel  *model = new QStandardItemModel();

    model->setColumnCount(2);

    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("卡号"));

    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("姓名"));
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);//表头显示居左
    FormReal::isNew++;
}

FormReal::~FormReal()
{
    delete ui;
    FormReal::isNew--;
}

void FormReal::on_pushButton_main_clicked()// 返回主页
{
    this->hide();
    m_Main->CreateMainBtn();
}

void FormReal::on_pushButton_last_clicked()//返回上一页
{
    this->hide();
    m_Main->CreateMainBtn();
}
