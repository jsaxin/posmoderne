#ifndef MENUITEM_H
#define MENUITEM_H

#include <QString>

class MenuItem
{
public:
    explicit MenuItem();

    QString name;
    QString description;
    float VAT;
    float price;
    int weight;
    int style;
};

#endif // MENUITEM_H
