#include "DatabaseHolder.h"

DatabaseHolder::DatabaseHolder(QObject *parent) :
    QObject(parent)
{
    QSettings settings;

    //Get database paths or use these defaults.
    QString menu_db_path = settings.value( "menu_db_path", QDir::homePath() + "/.posmoderne_menu.sqlite" ).toString();
    QString sales_db_path = settings.value( "sales_db_path", QDir::homePath() + "/.posmoderne_sales.sqlite" ).toString();
    QString app_db_path = settings.value( "app_db_path", QDir::homePath() + "/.posmoderne_app.sqlite" ).toString();

    //Run init on each of them.
    this->initDatabase(menu_db_path, MENU_DB);
    this->initDatabase(sales_db_path, SALES_DB);
    this->initDatabase(app_db_path, APP_DB);

    //Store settings again.
    settings.setValue("menu_db_path",menu_db_path);
    settings.setValue("sales_db_path",sales_db_path);
    settings.setValue("app_db_path",app_db_path);
}

DatabaseHolder::~DatabaseHolder()
{
    //Close all database connections.
    this->m_MenuDatabase.close();
    this->m_SalesDatabase.close();
    this->m_AppDatabase.close();
}


void DatabaseHolder::initDatabase(QString dbPath, DB_TYPE type)
{
    //Make db reference the correct connection. Menu is used as default since references must be allocated initialised.
    QSqlDatabase &db = this->m_MenuDatabase;
    if ( type == SALES_DB )
        db = this->m_SalesDatabase;
    if ( type == APP_DB )
        db = this->m_AppDatabase;

    //Setup connection
    db = QSqlDatabase::addDatabase("QSQLITE",dbPath);
    db.setDatabaseName(dbPath);

    //If it's there and can be opened, we're done.
    if (QFile(dbPath).exists() && db.open())
        return;

    //If it cannot be opened, we have a problem. Fail loudly and somewhat informatively.
    if ( !db.open() )
        qDebug() << "DatabaseHolder::initDatabase: Failed to open database: " << dbPath << db.lastError();

    QStringList queryList;

    //Append all queries necessary for table creation.
    if (type == MENU_DB)
    {

        queryList.append("create table if not exists \n"
                         "Menu (\n"
                         "MenuNr integer primary key autoincrement, \n"
                         "Name text, \n"
                         "Weight integer, \n"
                         "Style text \n"
                         ");\n");
        queryList.append("create table if not exists \n"
                         "Category (\n"
                         "CategoryNr integer primary key autoincrement, \n"
                         "MenuNr integer, \n"
                         "Name text, \n"
                         "Weight integer, \n"
                         "Style text \n"
                         ");\n");
        queryList.append("create table if not exists \n"
                         "MenuItem (\n"
                         "MenuItemNr integer primary key autoincrement, \n"
                         "CategoryNr integer, \n"
                         "Name text, \n"
                         "Description text, \n"
                         "VAT real, \n"
                         "Price real, \n"
                         "Weight integer, \n"
                         "Style text \n"
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
                         "Pitch (\n"
                         "PitchNr integer primary key autoincrement,\n"
                         "MenuItemNr integer, \n"
                         "TabNr integer, \n"
                         "Time integer, \n"
                         "Name text, \n"
                         "Description text, \n"
                         "VAT real, \n"
                         "Price real \n"
                         ");\n");
    }

    if (type == APP_DB)
    {
        queryList.append("create table if not exists \n"
                         "User (\n"
                         "UserNr integer primary key autoincrement,\n"
                         "PswHash integer, \n"
                         "PswSalt integer\n"
                         ");\n");
        queryList.append("create table if not exists \n"
                         "Log (\n"
                         "LogNr integer primary key autoincrement,\n"
                         "UserNr integer, \n"
                         "Time integer, \n"
                         "Entry text \n"
                         ");\n");
    }

    QSqlQuery query(db);

    //Execute all queries.
    for (int i = 0; i < queryList.size(); ++i)
    {
        query.prepare(queryList[i]);
        if ( !query.exec() )
            qDebug() << "Error creating table " << i << ": " << query.lastError();
    }
}


void DatabaseHolder::log(QString logEntry)
{
    QSqlQuery query(this->m_AppDatabase);

    query.prepare("insert into Log(UserNr, Time, Entry) \n"
                  "values(:usernr, :time, :entry);");
    query.bindValue(":usernr", this->currentUser());
    query.bindValue(":time", QDateTime::currentDateTime().toTime_t());
    query.bindValue(":entry", logEntry);

    if ( !query.exec() )
        qDebug() << "Error inserting log entry: " << query.lastError();
}
