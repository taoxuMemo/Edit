#ifndef CNETCONTHREAD_H
#define CNETCONTHREAD_H

#include"qthread.h"
#include"mainwindow.h"
class CNetConThread : public QThread
{
    Q_OBJECT
public:
    explicit CNetConThread(QObject *parent = 0);
   void stop();
private:
    void run();
    bool m_isrun;
    MainWindow *m_Main;
signals:
    void TestSignal(QString);
};

#endif // CNETCONTHREAD_H
