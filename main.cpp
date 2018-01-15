#include "mainwindow.h"
#include <QApplication>
#include "qdatatype.h"
#include"qmessagebox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
 //   w.setWindowFlags(w.windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
  //  w.setWindowFlags(w.windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
//    QString str;//="hah123fjdk";
 //   int aa=str.toInt();
    if(w.m_bRun)
        w.show();
    else
        QMessageBox::information(NULL,"异常信息","程序异常退出，请查看错误日志！！！！！！！！！");


    return a.exec();
}
