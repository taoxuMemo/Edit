#ifndef CRS232THREAD_H
#define CRS232THREAD_H

#include <QObject>
#include <QThread>

class CRs232Thread : public QThread
{
    Q_OBJECT
public:
    explicit CRs232Thread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CRS232THREAD_H
