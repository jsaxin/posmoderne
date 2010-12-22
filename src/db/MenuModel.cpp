#include "MenuModel.h"

MenuModel::MenuModel(QSqlDatabase *db, QObject *parent) :
    QSqlQueryModel(parent),
    mDb(db)
{
}
