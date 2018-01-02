#ifndef FORMSETTING_WLSZ_H
#define FORMSETTING_WLSZ_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormSetting_WLSZ;
}

class FormSetting_WLSZ : public QWidget
{
    Q_OBJECT

public:
    explicit FormSetting_WLSZ(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormSetting_WLSZ();
    MainWindow *m_Main;
    static int isNew;
private:
    Ui::FormSetting_WLSZ *ui;
};

#endif // FORMSETTING_WLSZ_H
