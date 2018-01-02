#ifndef FORMSETTING_CG_H
#define FORMSETTING_CG_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormSetting_CG;
}

class FormSetting_CG : public QWidget
{
    Q_OBJECT

public:
    explicit FormSetting_CG(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormSetting_CG();
    MainWindow *m_Main;
    static int isNew;
private:
    Ui::FormSetting_CG *ui;
};

#endif // FORMSETTING_CG_H
