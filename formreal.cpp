#include "formreal.h"
#include "ui_formreal.h"

#include"mainwindow.h"
#include "qdatetime.h"
int FormReal::isNew=0;
FormReal::FormReal(MainWindow *pMainWindow,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormReal)
{
    ui->setupUi(this);
    m_Main=pMainWindow;
    model = new QStandardItemModel();

    model->setColumnCount(3);

    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("时间"));

    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("方向"));

    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("长度"));

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);//表头显示居左
    FormReal::isNew++;
    connect(this, SIGNAL(TestSignal(int,int)), this, SLOT(DisplayMsg(int,int)));
}

FormReal::~FormReal()
{
    delete ui;
    FormReal::isNew--;
}

void FormReal::addlist(int nLen, int nFX)
{
    emit TestSignal(nLen,nFX);
}

void FormReal::DisplayMsg(int nLen, int nFX)
{
    QDateTime dt=QDateTime::currentDateTime();
    model->setItem(0, 0, new QStandardItem(dt.toString()));
    model->setItem(0, 1, new QStandardItem(QString::number(nFX)));
    model->setItem(0, 2, new QStandardItem(QString::number(nLen)));
    return;
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
