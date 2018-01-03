#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formmain.h"
#include"formreal.h"
#include"formabout.h"
#include"formanalysis.h"
#include"formhistory.h"
#include"formonline.h"
#include"formquery.h"
#include"formsetting.h"
#include"formstate.h"
#include"formsetting_ck.h"
#include"formsetting_sjjy.h"
#include "coperationconfig.h"
#include "qdatatype.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    COperationConfig * m_pOpera;
    unsigned char m_nCom[8];
    stuChannel m_stuChan[8];
    //****************************界面指针******************************************
    FormMain * m_fm;//主按钮界面
    FormAbout * m_fabout;
    FormReal * m_fr;//实时数据界面
    FormAnalysis * m_fanalysis;
    FormHistory * m_fhistory;
    FormOnline * m_fonline;
    FormQuery * m_fquery;
    FormSetting * m_fsetting;
    FormState * m_fstate;
    FormSetting_CK *m_fsetting_ck;
    FormSetting_SJJY *m_fsetting_sjjy;//时间设置界面指针
    //*************************初始化***************************************
    void init();
   //***************************创建界面函数****************************************
    void CreateMainBtn();
    void CreateRealTime();
    void CreateAbout();
    void CreateAnalysis();
    void CreateHistory();
    void CreateOnline();
    void CreateQuery();
    void CreateSetting();
    void CreateState();
    void CreateSetting_ck();
    void CreateSetting_sjjy();//时间校验界面启动函数
    int m_nTest;
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
