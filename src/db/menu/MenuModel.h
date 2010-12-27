#ifndef MENUMODEL_H
#define MENUMODEL_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class MenuModel : public QSqlQueryModel
{
Q_OBJECT
public:
    enum MENUMODEL_FIELDS{Menu, MenuCategory, Commodity, Name, Description, Price, Style, VAT};

    explicit MenuModel(QSqlDatabase &db, QObject *parent = 0);

    void setMenu(int menuNr){this->m_CurrentMenu = menuNr;}

//    int rowCount(const QModelIndex &parent = QModelIndex()) const;
//
    QVariant data(const QModelIndex &index, int role) const;
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
//
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
//    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
//    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
    QSqlDatabase m_Db;
    int m_CurrentMenu;

signals:

public slots:

};

#endif // MENUMODEL_H
