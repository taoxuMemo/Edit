#include "mainwindow.h"
#include <QApplication>
#include "qdatatype.h"
#include"qmessagebox.h"
#include"ctool.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
 //   w.setWindowFlags(w.windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
  //  w.setWindowFlags(w.windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
//    QString str;//="hah123fjdk";
 //   int aa=str.toInt();
//    char aa='5';
//    char bb='F';
//    int zz=CTool::chartohex8(aa,bb);
//    int i=52;
//    QString b=QString("%1").arg(i, 4, 10, QChar('0'));
    int nCRC=0x0D3F;
    QString c=QString("%1").arg(nCRC, CRCLENGTH, 16, QChar('0')).toUpper();
    QString str=c.toUpper();
    if(w.m_bRun)
        w.show();
    else
        QMessageBox::information(NULL,"异常信息","程序异常退出，请查看错误日志！！！！！！！！！");


    return a.exec();
}
