#ifndef DATABASEHOLDER_H
#define DATABASEHOLDER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>

class DatabaseHolder : public QObject
{
Q_OBJECT
public:
    enum DB_TYPE{MENU_DB,SALES_DB};

    explicit DatabaseHolder(QObject *parent = 0);
    ~DatabaseHolder();

    QSqlDatabase& menuDatabase(){return this->m_MenuDatabase;}
    QSqlDatabase& salesDatabase(){return this->m_SalesDatabase;}

    int currentUser(){return 0;}  //No users yet.

private:
    void initDatabase(QString dbPath, DB_TYPE type);

    QSqlDatabase m_MenuDatabase;
    QSqlDatabase m_SalesDatabase;

signals:

public slots:
    void log(QString logEntry);

};

#endif // DATABASEHOLDER_H
