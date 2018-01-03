#include "mainwindow.h"
#include <QApplication>
#include "qdatatype.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
 //   w.setWindowFlags(w.windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
  //  w.setWindowFlags(w.windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
    w.show();

    return a.exec();
}
