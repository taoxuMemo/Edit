#ifndef FORMREAL_H
#define FORMREAL_H

#include <QWidget>
#include"QStandardItem"
#include"QTableView"
class MainWindow;
namespace Ui {
class FormReal;
}

class FormReal : public QWidget
{
    Q_OBJECT

public:
    explicit FormReal(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormReal();
    void  addlist(int nLen,int nFX);
    MainWindow *m_Main;
    QStandardItemModel  *model;
    static int isNew;
signals:
    void TestSignal(int,int);
private slots:
    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

    void DisplayMsg(int ,int);

private:
    Ui::FormReal *ui;
};

#endif // FORMREAL_H
