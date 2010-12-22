#include "DatabaseHolder.h"

DatabaseHolder::DatabaseHolder(QObject *parent) :
    QObject(parent)
{
    QSettings settings;

    QString menu_db_path = settings.value( "menu_db_path", QDir::homePath() + "/.posmoderne_menu.sql" ).toString();
    QString sales_db_path = settings.value( "sales_db_path", QDir::homePath() + "/.posmoderne_sales.sql" ).toString();

    this->initDatabase(menu_db_path, MENU_DB);
    this->initDatabase(sales_db_path, SALES_DB);
    
    settings.setValue("menu_db_path",menu_db_path);
    settings.setValue("sales_db_path",sales_db_path);
}

DatabaseHolder::~DatabaseHolder()
{
    this->m_MenuDatabase.close();
    this->m_SalesDatabase.close();
}


void DatabaseHolder::initDatabase(QString dbPath, DB_TYPE type)
{
    //Make db reference the correct connection. Menu is used as default since references must be initialised.
    QSqlDatabase &db = this->m_MenuDatabase;
    if ( type == SALES_DB )
        db = this->m_SalesDatabase;

    //Setup connection
    db = QSqlDatabase::addDatabase("QSQLITE",dbPath);
    db.setDatabaseName(dbPath);

    if (QFile(dbPath).exists() && db.open())
        return;

    if ( !db.open() )
        qDebug() << db.lastError();

    QSqlQuery query(db);
    QStringList queryList;

    if (type == MENU_DB)
    {

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
                         "VAT real, \n"
                         "Price real, \n"
                         "Style text \n"
                         ");\n");
        queryList.append("create table if not exists \n"
                         "MenuItem (\n"
                         "MenuItemNr integer primary key autoincrement,\n"
                         "MenuNr integer, \n"
                         "MenuCategoryNr integer,\n"
                         "CommodityNr integer\n"
                         ");\n");
    }

    if (type == SALES_DB)
    {
        queryList.append("create table if not exists \n"
                         "Tab (\n"
                         "TabNr integer primary key autoincrement,\n"
                         "UserNr integer, \n"
                         "Opened integer, \n"
                         "Closed integer\n"
                         ");\n");
        queryList.append("create table if not exists \n"
                         "User (\n"
                         "UserNr integer primary key autoincrement,\n"
                         "PswHash integer, \n"
                         "PswSalt integer\n"
                         ");\n");
        queryList.append("create table if not exists \n"
                         "Pitch (\n"
                         "PitchNr integer primary key autoincrement,\n"
                         "CommodityNr integer, \n"
                         "TabNr integer, \n"
                         "Time integer, \n"
                         "Name text, \n"
                         "Description text, \n"
                         "VAT real, \n"
                         "Price real \n"
                         ");\n");
        queryList.append("create table if not exists \n"
                         "Log (\n"
                         "LogNr integer primary key autoincrement,\n"
                         "UserNr integer, \n"
                         "Time integer, \n"
                         "Entry text \n"
                         ");\n");
    }

    for (int i = 0; i < queryList.size(); i++)
    {
        query.prepare(queryList[i]);
        if ( !query.exec() )
            qDebug() << "Error creating table " << i << ": " << query.lastError();
    }
}


void DatabaseHolder::log(QString logEntry)
{
    QSqlQuery query(this->m_SalesDatabase);

    query.prepare("insert into Log(UserNr, Time, Entry) \n"
                  "values(:usernr, :time, :entry);");
    query.bindValue(":usernr", this->currentUser());
    query.bindValue(":time", QDateTime::currentDateTime().toTime_t());
    query.bindValue(":entry", logEntry);

    if ( !query.exec() )
        qDebug() << "Error inserting log entry: " << query.lastError();
}
