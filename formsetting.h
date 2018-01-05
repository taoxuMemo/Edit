#ifndef FORMSETTING_H
#define FORMSETTING_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormSetting;
}

class FormSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FormSetting(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormSetting();
    MainWindow *m_Main;
    static int isNew;


private slots:
    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::FormSetting *ui;
};

#endif // FORMSETTING_H
