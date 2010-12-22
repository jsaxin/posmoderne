#ifndef MENUHIERARCHICALPROXYMODEL_H
#define MENUHIERARCHICALPROXYMODEL_H

#include <QAbstractProxyModel>
#include <QSqlQuery>

class MenuHierarchicalProxyModel : public QAbstractProxyModel
{
Q_OBJECT
public:
    explicit MenuHierarchicalProxyModel(QObject *parent = 0);

signals:

public slots:

};

#endif // MENUHIERARCHICALPROXYMODEL_H
