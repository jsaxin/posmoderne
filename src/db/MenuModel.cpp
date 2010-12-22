#include "MenuModel.h"

MenuModel::MenuModel(QSqlDatabase &db, QObject *parent) :
    QSqlQueryModel(parent),
    m_Db(db)
{
}


QVariant MenuModel::data(const QModelIndex &index, int role) const
{
    //Guard.
    if ( role != Qt::DisplayRole )
        return QVariant();

    QSqlQuery query(this->m_Db);
    query.prepare("select MI.MenuNr, MI.MenuCategoryNr, MI.CommodityNr, C.Name, C.Description, C.Price, C.Style, C.VAT "\
                  "from Commodity C, MenuItem MI, Menu M, MenuCategory MC "\
                  "where C.CommodityNr=MI.CommodityNr "\
                  "and MI.MenuItemNr=:miNr ");

    query.bindValue(":miNr",index.row());

    if( !( query.exec() && query.next() ) )
        qDebug() << "Failed query in MenuModel::data: " << index << ": " << query.lastError();

    return query.value(index.column());
}

Qt::ItemFlags MenuModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);

    //Is given column editable?
    switch ( index.column() )
    {
    case Menu:
        flags &= ~Qt::ItemIsEditable;break; //No
    case MenuCategory:
        flags &= ~Qt::ItemIsEditable;break; //No
    case Commodity:
        flags &= ~Qt::ItemIsEditable;break; //No
    case Name:
        flags |= Qt::ItemIsEditable;break; //Yes
    case Description:
        flags |= Qt::ItemIsEditable;break; //Yes
    case Price:
        flags |= Qt::ItemIsEditable;break; //Yes
    case Style:
        flags |= Qt::ItemIsEditable;break; //Yes
    case VAT:
        flags |= Qt::ItemIsEditable;break; //Yes
    default:
        flags &= ~Qt::ItemIsEditable;break; //No
    }

    return flags;
}


bool MenuModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //Guard.
    if ( role != Qt::EditRole )
        return false;

    QSqlQuery query(this->m_Db);

    QString update_query("update ");

    switch ( index.column() )
    {
    case Menu:
        update_query.append("MenuItem MI set MI.MenuNr=:val ");break;
    case MenuCategory:
        update_query.append("MenuItem MI set MI.MenuCategoryNr=:val ");break;
    case Commodity:
        update_query.append("MenuItem MI set MI.CommodityNr=:val ");break;
    case Name:
        update_query.append("Commodity C set C.Name=:val ");break;
    case Description:
        update_query.append("Commodity C set C.Description=:val ");break;
    case Price:
        update_query.append("Commodity C set C.Price=:val ");break;
    case Style:
        update_query.append("Commodity C set C.Style=:val ");break;
    case VAT:
        update_query.append("Commodity C set C.VAT=:val ");break;
    default:
        return false;
    }

    update_query.append("where MI.MenuItemNr=:miNr");

    query.prepare(update_query);
    query.bindValue(":val",value);
    query.bindValue(":miNr",index.row());

    if (query.exec())
        return true;
    else
        qDebug() << "MenuModel::setData SQL error: " << update_query << query.lastError();

    return false;
}
