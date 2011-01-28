#include "MenuTreeModel.h"

MenuTreeModel::MenuTreeModel(QSqlDatabase db, QObject *parent) :
        QAbstractItemModel(parent),
        m_Db(db)
{
    if (!this->m_Db.isOpen())
        qDebug() << "MenuTreeModel: Database is not open.";
}

QStringList MenuTreeModel::menues()
{
    QStringList payload;
    QSqlQuery query(this->m_Db);
    query.prepare("select M.Name from Menu M order by M.Weight");

    if (!query.exec())
        qDebug() << "MenuTreeModel::menues failure: " << query.lastError();

    while (query.next())
        payload.append(query.value(0).toString());

    return payload;
}

QStringList MenuTreeModel::categories(int menu)
{
    if (menu == -1)
        menu = this->m_CurrentMenu;

    QStringList payload;
    QSqlQuery query(this->m_Db);
    query.prepare("select C.Name from Menu M, Category C where C.MenuNr=:mNr order by C.Weight");
    query.bindValue(":mNr",menu);

    if (!query.exec())
        qDebug() << "MenuTreeModel::categories failure: " << query.lastError();

    while (query.next())
        payload.append(query.value(0).toString());

    return payload;
}

QStringList MenuTreeModel::menuItems(int category, int menu)
{
    if (menu == -1)
        menu = this->m_CurrentMenu;

    QStringList payload;
    QSqlQuery query(this->m_Db);
    query.prepare("select MI.Name from Menu M, Category C, MenuItem MI where C.CategoryNr=:cNr and M.MenuNr=:mNr order by MI.Weight");
    query.bindValue(":cNr", category);
    query.bindValue(":mNr",menu);

    if (!query.exec())
        qDebug() << "MenuTreeModel::menuItems failure: " << query.lastError();

    while (query.next())
        payload.append(query.value(0).toString());

    return payload;
}
