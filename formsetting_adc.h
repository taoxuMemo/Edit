#ifndef FORMSETTING_ADC_H
#define FORMSETTING_ADC_H

#include <QWidget>
class MainWindow;
namespace Ui {
class FormSetting_ADC;
}

class FormSetting_ADC : public QWidget
{
    Q_OBJECT

public:
    explicit FormSetting_ADC(MainWindow *pMainWindow,QWidget *parent = 0);
    ~FormSetting_ADC();
    MainWindow *m_Main;
    static int isNew;
private:
    Ui::FormSetting_ADC *ui;
};

#endif // FORMSETTING_ADC_H
