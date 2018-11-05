#include "menuitem.h"

MenuItemGraphicsObject::MenuItemGraphicsObject(
    MenuItemGraphicsObject *ParentMenuItem,
    IMainMenuModel::IMenuItem *MenuItem,
    MetaInfo *ViewPluginMeta,
    QWidget *parent)
    : QWidget(parent)
{
    parentMenuItem = ParentMenuItem;
    menuItem = MenuItem;
    viewPluginMeta = ViewPluginMeta;

    pressed = false;
    setFlag(ItemIsMovable);
    FormatMenuItemName(viewPluginMeta->Name);
    boundRect = QRectF(0, 0, 100, 100);
}

MenuItemGraphicsObject::MenuItemGraphicsObject(QString name, QWidget *parent) : QWidget(parent)
{
    pressed = false;
    setFlag(ItemIsMovable);
    FormatMenuItemName(name);
    boundRect = QRectF(0, 0, 100, 100);
}

void MenuItemGraphicsObject::FormatMenuItemName(QString name)
{
    QRegExp regExp = QRegExp("([A-Z]+[a-z]+)");
    regExp.setCaseSensitivity(Qt::CaseSensitive);
    int pos = 0;
    QStringList list;
    while(pos >= 0)
    {
        pos = regExp.indexIn(name, pos);
        if(pos == -1)
        {
            break;
        }
        list.append(regExp.cap(0));
        pos += list.last().length();
    }

    for(int i = 0; i < list.count(); ++i)
    {
        if(i == 0)
        {
            itemMenuName += list[i];
        }
        else if(i == list.count() - 1)
        {
            if(list[i].toLower() == "view")
            {
                break;
            }
            itemMenuName += "\r\n" + list[i];
        }
        else
        {
            itemMenuName += "\r\n" + list[i];
        }
    }
}

QRectF MenuItemGraphicsObject::boundingRect() const
{
    return boundRect;
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
    painter->setFont(QFont("Arial", rect.width() / 10));
    painter->drawText(rect, Qt::AlignCenter, itemMenuName);
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
    {
        emit OnClicked(this);
    }
}
