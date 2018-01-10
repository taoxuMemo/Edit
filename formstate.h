#ifndef FORMSTATE_H
#define FORMSTATE_H

#include <QWidget>
#include"qstandarditemmodel.h"
class MainWindow;
namespace Ui {
class FormState;
}

class FormState : public QWidget
{
    Q_OBJECT

public:
    explicit FormState(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormState();
    MainWindow *m_Main;
    static int isNew;
    //添加数据nType1:网络 2:串口 3:模拟量 4:开关量
    //nRow 行号
    bool AddItemStatus(int nType,int nRow,QString sPZ,QString sZT,QString sSJ);
    bool initTL();
    QStandardItemModel *model;
    QStandardItemModel *modelCK;
    QStandardItemModel *modelMNL;
    QStandardItemModel *modelKGL;
private slots:
    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

    void on_pushButton_clicked();

private:
    Ui::FormState *ui;
};

#endif // FORMSTATE_H
