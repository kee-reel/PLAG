#include "treeitem.h"

TreeItem::TreeItem()
{
    parentItem = NULL;
    itemData.append(QVariant(""));
    itemData.append(QVariant(-1));
}

TreeItem::TreeItem(TreeItem *parent, QList<QVariant> data)
{
    parentItem = parent;
    for(int i = 0; i < data.count(); i++)
        itemData.append(data[i]);
}

TreeItem::~TreeItem()
{
    if(childItems.count())
        for(int i = 0; i < childItems.count(); i++)
            delete childItems[i];
}

void TreeItem::SetChilds(QList<TreeItem *> childs)
{
    childItems = childs;
}

void TreeItem::AddChild(int row, TreeItem *child)
{
    childItems.insert(row, child);
}

QVariant TreeItem::GetData(int column)
{
    return (column < itemData.count()) ? itemData[column] : QVariant();
}

void TreeItem::SetData(int column, QVariant data)
{
    if(column < itemData.count())
        itemData[column] = data;
}
