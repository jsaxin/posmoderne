#ifndef MENU_H
#define MENU_H

#include <QMap>

#include "MenuCategory.h"

class Menu
{
public:
    explicit Menu();

    MenuCategory operator[](int category) { return this->m_Categories.value(category); }

private:
    int m_MenuNr;
    int m_Weight;
    QString m_Name;
    QString m_Style;
    QMap<int, MenuCategory> m_Categories;
};

#endif // MENU_H
