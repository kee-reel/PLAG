#ifndef MENUITEM_H
#define MENUITEM_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QWidget>
#include <QRegExp>
#include <QEvent>
#include <QStringList>

#include "../MainMenuModelPlugin/imainmenumodule.h"

class MenuItemGraphicsObject : public QWidget, public QGraphicsItem
{
    Q_OBJECT
    void FormatMenuItemName(QString name);

public:
    MenuItemGraphicsObject(MenuItemGraphicsObject *ParentMenuItem, IMainMenuPluginModel::MenuItem *MenuItemGraphicsObject, MetaInfo *ViewPlugin, QWidget *parent = 0);
    MenuItemGraphicsObject(QString name, QWidget *parent = 0);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void OnClicked(IMainMenuPluginModel::MenuItem *menuItem, MetaInfo *viewMeta);

protected:
    bool pressed;
    int dx, dy;
    IMainMenuPluginModel::MenuItem *menuItem;
    MetaInfo *viewPluginMeta;
    QString itemMenuName;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    // QObject interface
public:
    bool event(QEvent *event) override;
};

#endif // MENUITEM_H
