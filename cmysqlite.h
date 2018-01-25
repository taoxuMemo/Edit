#ifndef CMYSQLITE_H
#define CMYSQLITE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
class CMySqlite : public QObject
{
    Q_OBJECT
public:
    explicit CMySqlite(QObject *parent = nullptr);
    QSqlDatabase database;
    bool init();
    bool InsertRD(QString sCoding,QString sType,double dValue);
signals:

public slots:
};

#endif // CMYSQLITE_H
