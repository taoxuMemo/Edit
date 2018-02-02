#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QWidget>
//#include"mainwindow.h"
class MainWindow;
namespace Ui {
class FormMain;
}

class FormMain : public QWidget
{
    Q_OBJECT

public:

    explicit FormMain(QWidget *parent = 0);
    FormMain(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormMain();

    MainWindow *m_Main;

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

    void on_pushButton_history_clicked();

    void on_pushButton_analysis_clicked();

    void on_pushButton_online_clicked();

    void on_pushButton_query_clicked();

    void on_pushButton_state_clicked();

    void on_pushButton_setting_clicked();

    void on_pushButton_about_clicked();

    void on_pushButton_clicked();

private:
    Ui::FormMain *ui;


};

#endif // FORMMAIN_H
