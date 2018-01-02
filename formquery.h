#ifndef FORMQUERY_H
#define FORMQUERY_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormQuery;
}

class FormQuery : public QWidget
{
    Q_OBJECT

public:
    explicit FormQuery(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormQuery();
    MainWindow *m_Main;
    static int isNew;
private slots:
    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

private:
    Ui::FormQuery *ui;
};

#endif // FORMQUERY_H
