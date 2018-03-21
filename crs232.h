#ifndef CRS232_H
#define CRS232_H

#include <QObject>
#include "QtSerialPort/qserialport.h"
#include "QtSerialPort/qserialportinfo.h"
#include "QByteArray"
class MainWindow;
class CRs232 : public QObject
{
    Q_OBJECT
public:
    explicit CRs232(QObject *parent = nullptr);
    QSerialPort* myserial ;
    MainWindow *m_pMain;
    bool start();
    QByteArray m_baData;
signals:
     void Read_Data();
public slots:
};

#endif // CRS232_H
