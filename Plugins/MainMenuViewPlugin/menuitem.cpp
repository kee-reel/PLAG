#include "menuitem.h"

MenuItemGraphicsObject::MenuItemGraphicsObject(MenuItemGraphicsObject *ParentMenuItem, IMainMenuPluginModel::MenuItem *MenuItem, QWidget *parent)
    : QWidget(parent)
{
    menuItem = MenuItem;
    pressed = false;
    setFlag(ItemIsMovable);
}

QRectF MenuItemGraphicsObject::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void MenuItemGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush whiteBrush(Qt::white);
    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    blackPen.setWidth(3);
    painter->setPen(blackPen);
    painter->setFont(QFont("Arial", 14));
    painter->setFont(QFont("Arial", rect.width()/10));
    painter->drawText(rect, Qt::AlignCenter, menuItem->meta->Name);
    painter->drawEllipse(rect);
}

void MenuItemGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    dx = event->scenePos().x();
    dy = event->scenePos().y();
    QGraphicsItem::update();
    QGraphicsItem::mousePressEvent(event);
}

void MenuItemGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    dx = dx - event->scenePos().x();
    dy = dy - event->scenePos().y();

    QGraphicsItem::update();
    QGraphicsItem::mouseReleaseEvent(event);
    if((dx + dy) == 0)
        emit OnClicked(menuItem);
}

bool MenuItemGraphicsObject::event(QEvent *event)
{
}
