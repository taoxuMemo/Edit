#ifndef FORMSETTING_YZSB_H
#define FORMSETTING_YZSB_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormSetting_YZSB;
}

class FormSetting_YZSB : public QWidget
{
    Q_OBJECT

public:
    explicit FormSetting_YZSB(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormSetting_YZSB();
    MainWindow *m_Main;
    static int isNew;
private:
    Ui::FormSetting_YZSB *ui;
};

#endif // FORMSETTING_YZSB_H
