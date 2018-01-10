#ifndef CMYTHREAD_H
#define CMYTHREAD_H
#include"QThread"

class CMyThread : public QThread
{
    Q_OBJECT
public:
    CMyThread();
    void run();
};

#endif // CMYTHREAD_H
