#include "crs232.h"
#include "mainwindow.h"
CRs232::CRs232(QObject *parent) : QObject(parent)
{
    m_pMain=(MainWindow*)parent;
}
bool CRs232::start()
{
    myserial = new QSerialPort;
    //设置串口名

    myserial->setPortName("ttyUSB0");

    this->myserial->setBaudRate(115200,QSerialPort::AllDirections);//设置波特率；QSerialPort::AllDirections：双工

    this->myserial->setDataBits(QSerialPort::Data8);//数据位

    this->myserial->setParity(QSerialPort::NoParity);//校验位

    this->myserial->setStopBits(QSerialPort::OneStop);//停止位
    // this->myserial->waitForReadyRead(10);
    this->myserial->setFlowControl(QSerialPort::NoFlowControl);//流控制
    if(this->myserial->open(QIODevice::ReadWrite)==false)
    {
        COperationConfig::writelog(ERROROPENCOM);
        return false;
    }

    connect(myserial, SIGNAL(readyRead()), this, SLOT(ReadData())); //单片解数据接收巢

    return true;
}
void CRs232::ReadData()
{
    QByteArray buf;
    if(m_baData.size()>2046)
        m_baData.clear();
    buf = myserial->readAll();

    COperationConfig::writeRD(QString(buf));

    //写入本地实时数据日志文件
    if(!buf.isEmpty())
    {
        for(int i=0;i<buf.size();i++)
        {
            if(buf.at(i)=='#')
            {
                m_baData.append('#');
            }else if(buf.at(i)=='\n')
            {
                m_baData.append('\n');
                m_pMain->RecvData(m_baData);
                m_baData.clear();
            }else
            {
                if(m_baData.size()>1)
                    m_baData.append(buf.at(i));
            }
        }
    }
    buf.clear();
}
