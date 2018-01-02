#ifndef FORMSETTING_SB_H
#define FORMSETTING_SB_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormSetting_SB;
}

class FormSetting_SB : public QWidget
{
    Q_OBJECT

public:
    explicit FormSetting_SB(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormSetting_SB();
    MainWindow *m_Main;
    static int isNew;
private:
    Ui::FormSetting_SB *ui;
};

#endif // FORMSETTING_SB_H
