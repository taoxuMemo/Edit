#ifndef FORMSTATE_H
#define FORMSTATE_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormState;
}

class FormState : public QWidget
{
    Q_OBJECT

public:
    explicit FormState(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormState();
    MainWindow *m_Main;
    static int isNew;
private slots:
    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

private:
    Ui::FormState *ui;
};

#endif // FORMSTATE_H
