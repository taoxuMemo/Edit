#ifndef FORMONLINE_H
#define FORMONLINE_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormOnline;
}

class FormOnline : public QWidget
{
    Q_OBJECT

public:
    explicit FormOnline(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormOnline();
    MainWindow *m_Main;
    static int isNew;
private slots:
    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

private:
    Ui::FormOnline *ui;
};

#endif // FORMONLINE_H
