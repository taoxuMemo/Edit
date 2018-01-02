#ifndef FORMREAL_H
#define FORMREAL_H

#include <QWidget>
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
    MainWindow *m_Main;
    static int isNew;
private slots:
    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

private:
    Ui::FormReal *ui;
};

#endif // FORMREAL_H
