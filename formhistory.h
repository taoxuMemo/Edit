#ifndef FORMHISTORY_H
#define FORMHISTORY_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormHistory;
}

class FormHistory : public QWidget
{
    Q_OBJECT

public:
    explicit FormHistory(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormHistory();
    MainWindow *m_Main;
    static int isNew;
private slots:
    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

private:
    Ui::FormHistory *ui;
};

#endif // FORMHISTORY_H
