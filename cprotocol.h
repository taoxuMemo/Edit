#ifndef CPROTOCOL_H
#define CPROTOCOL_H

#include <QObject>

class CProtocol : public QObject
{
    Q_OBJECT
public:
    explicit CProtocol(QObject *parent = nullptr);
    bool DataAnalysis(char * pData, int nLen);
signals:

public slots:
};

#endif // CPROTOCOL_H
