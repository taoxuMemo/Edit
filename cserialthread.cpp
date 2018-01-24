#include "cserialthread.h"

CSerialThread::CSerialThread(QObject *parent): QThread(parent)
{
    m_Main=(MainWindow*)parent;
}
void CSerialThread::stop()
{
    m_isrun=false;
}
void CSerialThread::run()
{

}
