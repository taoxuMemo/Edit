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
#include "formsetting_wlsz.h"
#include "coperationconfig.h"
//#include "qdatatype.h"
#include"cmysocketthread.h"

#include"qstringlistmodel.h"
#include "cmysocket.h"
#include "cnetconthread.h"
#include "qqueue.h"
#include "cdbstjc.h"
#include "cmysqlite.h"
#include "ctesttcpthd.h"
class CMySocketThread;
class CNetConThread;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void timerEvent( QTimerEvent *event );

    bool m_bRun;
    COperationConfig * m_pOpera;
    unsigned char m_nCom[8];
    stuChannel  m_stuChan[8];
    stuIPAddr   m_stuIPA[8];
    QString     m_sSBWYBS;
    QString     m_sPassWD;
    bool       m_bXY;   //true是TCP    flase是UDP

    QQueue<QString> m_queCom;   //接收com发来的数据
    QQueue<QString> m_queTcp;   //接收tcp发来的数据

  //  CDBSTJC     m_DBSTJC;       //地表项处理函数
    CJCBase     *m_pBase;
 //   QQueue m_queTcp<QString,int>;  //接收tcp发来的数据
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
    FormSetting_SJJY *m_fsetting_sjjy;  //时间设置界面指针
    FormSetting_WLSZ *m_fsetting_wlsz;  //网络设置界面指针
    CMySocket * m_pMySocket[6];

    CMySqlite m_mySql;                  //数据库操作类

    CTestTcpThd *m_pthdTest;              //
    //*************************初始化***************************************
    bool init();
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
    void CreateSetting_wlsz();//网络参数设置
    void CreateSetting_sjjy();//时间校验界面启动函数
    int m_nTest;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void DisplayMsg(QString);

    void SerialData(QString);
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    QStringListModel * m_model;

    CMySocketThread * m_pMyThread;
    CNetConThread   * m_pNetConThread;
//    CMySocketThread  * m_pMyThread;
  //  bool m_isRun;
};

#endif // MAINWINDOW_H
