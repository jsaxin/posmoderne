#include "DatabaseHolder.h"

DatabaseHolder::DatabaseHolder(QObject *parent) :
    QObject(parent)
{
    QSettings settings;

    QString dbPath = settings.value( "db_path", QDir::homePath() + "/posmoderne.sql" ).toString();

    if (QFile(dbPath).exists())
    {
        this->mDatabase = QSqlDatabase::addDatabase("QSQLITE",dbPath);
        this->mDatabase.setDatabaseName(dbPath);
    }
    else
        this->setupDatabase(dbPath);

    if ( !this->mDatabase.open() )
        qDebug() << "Failed to open database " << dbPath << ": " << this->mDatabase.lastError();
}


void DatabaseHolder::setupDatabase(QString dbPath)
{
    this->mDatabase = QSqlDatabase::addDatabase("QSQLITE",dbPath);
    this->mDatabase.setDatabaseName(dbPath);

    if ( !this->mDatabase.open() )
        qDebug() << this->mDatabase.lastError();

    QSqlQuery query(this->mDatabase);
    QStringList queryList;

    queryList.append("create table if not exists \n"
                      "Menu (\n"
                      "MenuNr integer primary key autoincrement, \n"
                      "Name text, \n"
                      "Style text \n"
                      ");\n");
    queryList.append("create table if not exists \n"
                     "MenuCategory (\n"
                     "MenuCategoryNr integer primary key autoincrement, \n"
                     "Name text, \n"
                     "Style text \n"
                     ");\n");
    queryList.append("create table if not exists \n"
                     "Commodity (\n"
                     "CommodityNr integer primary key autoincrement, \n"
                     "Name text, \n"
                     "Description text, \n"
                     "Price real, \n"
                     "Style text \n"
                     ");\n");
    queryList.append("create table if not exists \n"
                     "MenuItem (\n"
                     "MenuItemNr integer primary key autoincrement,\n"
                     "MenuNr integer, \n"
                     "MenuCategoryNr integer,\n"
                     "CommodityNr integer,\n"
                     "foreign key(MenuNr) references Menu(MenuNr),\n"
                     "foreign key(MenuCategoryNr) references MenuCategory(MenuCategoryNr),\n"
                     "foreign key(CommodityNr) references Commodity(CommodityNr)\n"
                     ");\n");

    for (int i = 0; i < queryList.size(); i++)
    {
        query.prepare(queryList[i]);
        if ( !query.exec() )
            qDebug() << "Error creating table " << i << ": " << query.lastError();
    }
}
