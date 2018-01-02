#ifndef FORMSETTING_SJJY_H
#define FORMSETTING_SJJY_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormSetting_SJJY;
}

class FormSetting_SJJY : public QWidget
{
    Q_OBJECT

public:
    explicit FormSetting_SJJY(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormSetting_SJJY();
    MainWindow *m_Main;
    static int isNew;
private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FormSetting_SJJY *ui;
};

#endif // FORMSETTING_SJJY_H
