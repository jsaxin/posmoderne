#ifndef MENU_H
#define MENU_H

#include <QMap>
#include <QObject>

#include "MenuCategory.h"

class Menu : public QObject
{
Q_OBJECT
public:
    explicit Menu(QObject *parent = 0);

private:
    QMap<int, MenuCategory> m_categories;

signals:

public slots:

};

#endif // MENU_H
