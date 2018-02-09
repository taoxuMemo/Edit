#ifndef FTPMANAGER_H
#define FTPMANAGER_H

#include <QObject>

class FTPManager : public QObject
{
    Q_OBJECT
public:
    explicit FTPManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FTPMANAGER_H