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

class DatabaseHolder : public QObject
{
Q_OBJECT
public:
    explicit DatabaseHolder(QObject *parent = 0);
    ~DatabaseHolder(){this->mDatabase.close();}

    void setupDatabase(QString dbPath);

    QSqlDatabase& connection(){return this->mDatabase;}

private:
    QSqlDatabase mDatabase;

signals:

public slots:

};

#endif // DATABASEHOLDER_H
