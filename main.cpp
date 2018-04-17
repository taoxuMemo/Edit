#include "mainwindow.h"
#include <QApplication>
#include "qdatatype.h"
#include"qmessagebox.h"
#include"ctool.h"
#include "QDateTime"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    QDateTime dt=QDateTime::currentDateTime();
//    QDateTime  dt1 = QDateTime::fromString("2018-03-02 09:07:00", "yyyy-MM-dd hh:mm:ss");
//    int nSec=dt1.secsTo(dt);
//    QString strDou="--";
//    double dou=strDou.toDouble();
//    if(dou==0.2)
//        {
//        int aaaaa=1000;
//    }
//    QList<QString> list1;
//    list1.insert(0,"aaaa");
//    list1.insert(0,"bbbb");
//    list1.insert(0,"cccc");
//    list1.append("ddd");
//    list1.insert(0,"eeee");
//    list1.insert(0,"ffff");
//    int nList=list1.size();
//    QString str1=list1.takeAt(0);
//    QString str2=list1.takeAt(0);
//    QString str3=list1.takeAt(0);
//    list1.removeAt(1);;
    QString b=QString("%1").arg(234, DATALENGTH, 10, QChar('0'));
    if(w.m_bRun)
        w.show();
    else
        QMessageBox::information(NULL,"异常信息","程序异常退出，请查看错误日志！！！！！！！！！");


    return a.exec();
}
