#ifndef MENUTREEMODEL_H
#define MENUTREEMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class MenuTreeModel : public QAbstractItemModel
{
Q_OBJECT
public:
    explicit MenuTreeModel(QSqlDatabase db, QObject *parent = 0);

    QStringList menues();
    void setMenu(int menu){this->m_CurrentMenu = menu;}
    QStringList categories(int menu = -1);
    QStringList menuItems(int category, int menu = -1);

private:
    QSqlDatabase m_Db;
    int m_CurrentMenu;

signals:

public slots:

};

#endif // MENUTREEMODEL_H
