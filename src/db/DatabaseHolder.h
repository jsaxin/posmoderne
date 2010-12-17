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
    explicit DatabaseHolder(QObject *parent = 0);
    ~DatabaseHolder(){this->mDatabase.close();}

    QSqlDatabase& connection(){return this->mDatabase;}

    int currentUser(){return 0;}  //No users yet.

private:
    void setupDatabase(QString dbPath);

    QSqlDatabase mDatabase;

signals:

public slots:
    void log(QString logEntry);

};

#endif // DATABASEHOLDER_H
