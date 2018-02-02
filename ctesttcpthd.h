#ifndef CTESTTCPTHD_H
#define CTESTTCPTHD_H

#include <QObject>
#include <qthread.h>
#include<qtcpsocket.h>
#include<qtcpserver.h>
class MainWindow;
class CTestTcpThd : public QThread
{
    Q_OBJECT
public:
    explicit CTestTcpThd(QObject *parent = nullptr);
    void stop();
    void MyListen();
protected:
    void run();
    bool m_bTag;
    MainWindow *m_pMain;
    QTcpServer *m_MyTcpSvr;
    QTcpSocket *m_MyTcpSocket;
    bool m_bCon; //是否连接
signals:

public slots:
    void processNewConnection();

    void readMessage();

    void removeUserFormList();
};

#endif // CTESTTCPTHD_H
