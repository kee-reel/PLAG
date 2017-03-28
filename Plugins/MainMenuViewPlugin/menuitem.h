#ifndef MENUITEM_H
#define MENUITEM_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QEvent>

#include "../MainMenuModelPlugin/imainmenumodule.h"

class MenuItemGraphicsObject : public QWidget, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MenuItemGraphicsObject(MenuItemGraphicsObject *ParentMenuItem, IMainMenuPluginModel::MenuItem *MenuItemGraphicsObject, QWidget *parent = 0);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void OnClicked(IMainMenuPluginModel::MenuItem *menuItem);

protected:
    bool pressed;
    int dx, dy;
    IMainMenuPluginModel::MenuItem *menuItem;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // QObject interface
public:
    bool event(QEvent *event) override;
};

#endif // MENUITEM_H
