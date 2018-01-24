#ifndef CSERIALTHREAD_H
#define CSERIALTHREAD_H

#include "qthread.h"
class MainWindow;
class CSerialThread : public QThread
{
    Q_OBJECT
public:
   explicit CSerialThread(QObject *parent = 0);
     void stop();
private:
    void run();
    bool m_isrun;
    MainWindow *m_Main;
signals:
    void TestSignal(QString);
};

#endif // CSERIALTHREAD_H
