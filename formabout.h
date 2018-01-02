#ifndef FORMABOUT_H
#define FORMABOUT_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormAbout;
}

class FormAbout : public QWidget
{
    Q_OBJECT

public:
    explicit FormAbout(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormAbout();
    MainWindow *m_Main;
    static int isNew;
private slots:
    void on_pushButton_last_clicked();

    void on_pushButton_main_clicked();

private:
    Ui::FormAbout *ui;
};

#endif // FORMABOUT_H
