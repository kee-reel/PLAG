#ifndef MENUITEM_H
#define MENUITEM_H

#include <QGraphicsItem>

class MenuItem : public QGraphicsItem
{
public:
    MenuItem();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MENUITEM_H
