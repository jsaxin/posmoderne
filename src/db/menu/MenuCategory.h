#ifndef MENUCATEGORY_H
#define MENUCATEGORY_H

#include <QObject>
#include <QMap>

#include "MenuItem.h"

class MenuCategory : public QObject
{
Q_OBJECT
public:
    explicit MenuCategory(QObject *parent = 0);

private:
    QMap<int, MenuItem> m_menuItems;
signals:

public slots:

};

#endif // MENUCATEGORY_H
