#ifndef CSERIALTHREAD_H
#define CSERIALTHREAD_H

#include "qthread.h"
#include "qlist.h"
class MainWindow;
class CSerialThread : public QThread
{
    Q_OBJECT
public:
   explicit CSerialThread(QObject *parent = 0);
   void stop();

   bool SetParam(QString name,int nbaud);
   bool SendData(QString);
   bool RecvData(QString&);
   bool TestXY(char *pD,int nSize);
   QList<QString> m_list;
   char m_sData[2048];
   QString m_strData;
   int m_fd;

private:
    void run();
    bool m_isrun;
    MainWindow *m_Main;
signals:
    void TestSignal(QString);
};

#endif // CSERIALTHREAD_H
