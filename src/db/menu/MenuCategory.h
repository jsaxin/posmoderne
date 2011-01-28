#ifndef MENUCATEGORY_H
#define MENUCATEGORY_H

#include <QMap>

#include "MenuItem.h"

class MenuCategory
{
public:
    explicit MenuCategory();

private:
    QMap<int, MenuItem> m_MenuItems;
};

#endif // MENUCATEGORY_H
