#include "treeitem.h"

TreeItem::TreeItem()
{
    parentItem = NULL;
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
