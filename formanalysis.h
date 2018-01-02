#ifndef FORMANALYSIS_H
#define FORMANALYSIS_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormAnalysis;
}

class FormAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit FormAnalysis(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormAnalysis();
    MainWindow *m_Main;
    static int isNew;
private slots:
    void on_pushButton_main_clicked();

    void on_pushButton_last_clicked();

private:
    Ui::FormAnalysis *ui;
};

#endif // FORMANALYSIS_H
