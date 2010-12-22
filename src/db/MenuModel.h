#ifndef MENUMODEL_H
#define MENUMODEL_H

#include <QSqlQueryModel>

class MenuModel : public QSqlQueryModel
{
Q_OBJECT
public:
    explicit MenuModel(QSqlDatabase *db, QObject *parent = 0);

//    int rowCount(const QModelIndex &parent = QModelIndex()) const;
//
//    QVariant data(const QModelIndex &index, int role) const;
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
//    Qt::ItemFlags flags(const QModelIndex &index) const;
//
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
//    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
//    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
    QSqlDatabase *mDb;

signals:

public slots:

};

#endif // MENUMODEL_H
