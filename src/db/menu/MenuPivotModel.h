#ifndef MENUPIVOTMODEL_H
#define MENUPIVOTMODEL_H

#include <QAbstractProxyModel>
#include <QSqlQuery>

#include "MenuModel.h"
#include "Menu.h"

class MenuPivotModel : public QAbstractProxyModel
{
Q_OBJECT
public:
    explicit MenuPivotModel(QObject *parent = 0);

private:

signals:

public slots:

};

#endif // MENUPIVOTMODEL_H
