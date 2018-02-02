#include "ctesttcpthd.h"
#include "mainwindow.h"
#include"QMessageBox"
CTestTcpThd::CTestTcpThd(QObject *parent) : QThread(parent)
{
    m_bTag=false;
    m_pMain=(MainWindow*)parent;
    m_MyTcpSvr=new QTcpServer();
    connect(m_MyTcpSvr, SIGNAL(newConnection()), this, SLOT(processNewConnection()));
}
void CTestTcpThd::run()
{
    ;
}
void CTestTcpThd::stop()
{
    m_bTag=false;


}
void CTestTcpThd::MyListen()
{
    QString strIP,strPort;

    if(m_MyTcpSvr->listen(QHostAddress::Any, 6200)==false)
    {
    //    QMessageBox::about(this,"message","error!!!");
    }
    else
    {
    //    QMessageBox::about(this,"提示","连接成功");
     //   QMessageBox::about(this,"message","sucess!!!");
    }
}
void CTestTcpThd::processNewConnection()
{
 //   QMessageBox::about(this,"message","connectone!!");
    m_MyTcpSocket = m_MyTcpSvr->nextPendingConnection();

    connect(m_MyTcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(m_MyTcpSocket,SIGNAL(disconnected()),this,SLOT(removeUserFormList()));

}

void CTestTcpThd::readMessage()
{
    int a=10;
 //   ui->textEdit->setText("connect 1");
    QByteArray arr =m_MyTcpSocket->readAll();
    QString ss=arr;
    m_pMain->m_DBSTJC.SerialInterFace(ss.toLatin1().data(),ss.length(),2);
//    ui->textEdit->setText(ss);
}
void CTestTcpThd::removeUserFormList()
{
  //  QMessageBox::about(this,"message","duankailianjie!!!");
}
