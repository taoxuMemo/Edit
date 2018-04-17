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
    initTL();
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
bool FormState::initTL()
{
    model = new QStandardItemModel();
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("ID"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("配置"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("时间"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("状态"));
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    modelCK = new QStandardItemModel();
    modelCK->setColumnCount(4);
    modelCK->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("ID"));
    modelCK->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("配置"));
    modelCK->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("时间"));
    modelCK->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("状态"));
    ui->tableView_2->setModel(modelCK);
    ui->tableView_2->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    modelMNL = new QStandardItemModel();
    modelMNL->setColumnCount(4);
    modelMNL->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("ID"));
    modelMNL->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("配置"));
    modelMNL->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("时间"));
    modelMNL->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("状态"));
    ui->tableView_3->setModel(modelMNL);
    ui->tableView_3->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    modelKGL = new QStandardItemModel();
    modelKGL->setColumnCount(4);
    modelKGL->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("ID"));
    modelKGL->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("配置"));
    modelKGL->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("时间"));
    modelKGL->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("状态"));
    ui->tableView_4->setModel(modelKGL);
    ui->tableView_4->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    return true;

}

bool FormState::AddItemStatus(int nType, int nRow, QString sPZ, QString sZT, QString sSJ)
{
   // QTableView *pTableView;
    QStandardItemModel *pmodel;
    QString strName;
    switch(nType)
    {
    case 1:
        pmodel=model;
     //   pTableView=ui->tableView;
        strName="网络";
        break;
    case 2:
        pmodel=modelCK;
     //   pTableView=ui->tableView_2;
        strName="串口";
        break;
    case 3:
        pmodel=modelMNL;
     //  pTableView=ui->tableView_3;
        strName="模拟量";
        break;
    case 4:
        pmodel=modelKGL;
     //   pTableView=ui->tableView_4;
        strName="开关量";
        break;
    default:
        break;
    }
    strName+=QString::number(nRow);
    pmodel->setItem(nRow,0,new QStandardItem(strName));
    pmodel->setItem(nRow,1,new QStandardItem(sPZ));
    pmodel->setItem(nRow,2,new QStandardItem(sZT));
    pmodel->setItem(nRow,3,new QStandardItem(sSJ));
    return true;
}

void FormState::on_pushButton_clicked()
{
    static int i=10;
    i++;
    QString str=QString::number(i);
    AddItemStatus(2,2,str,"fasfs:dsa","的撒大赛");

}
