#ifndef FORMSETTING_CK_H
#define FORMSETTING_CK_H

#include <QWidget>
//#include"datatype.h"
class MainWindow;
namespace Ui {
class FormSetting_CK;
}

class FormSetting_CK : public QWidget
{
    Q_OBJECT

public:
    explicit FormSetting_CK(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormSetting_CK();
    MainWindow *m_Main;
    static int isNew;
private slots:
    void on_pushButton_last_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::FormSetting_CK *ui;
};

#endif // FORMSETTING_CK_H
