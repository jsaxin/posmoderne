#ifndef MENUITEM_H
#define MENUITEM_H

#include <QObject>

class MenuItem : public QObject
{
Q_OBJECT
public:
    explicit MenuItem(QObject *parent = 0);

    QString name;
    QString description;
    float VAT;
    float price;
    int weight;
    int style;

signals:

public slots:

};

#endif // MENUITEM_H
