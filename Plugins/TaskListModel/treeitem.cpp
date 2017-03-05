#include "treeitem.h"
#include <QDebug>

TreeItem::TreeItem()
{
    parentItem = NULL;
}

TreeItem::TreeItem(TreeItem *parent, TreeItem *copy)
{
    qDebug() << copy;
    parentItem = parent;
    itemData.id = copy->itemData.id;
    itemData.dataChunks = copy->itemData.dataChunks;
    activeChunkName = copy->activeChunkName;
    activeChunk = &itemData.dataChunks[activeChunkName];
}

TreeItem::TreeItem(TreeItem *parent, int id, QString chunkName, QMap<QString, QVector<QVariant>> dataChunks)
{
    parentItem = parent;
    itemData.id = id;
    itemData.dataChunks = dataChunks;
    activeChunkName = chunkName;
    activeChunk = &itemData.dataChunks[activeChunkName];
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

void TreeItem::RemoveChild(TreeItem *child)
{
    childItems.removeOne(child);
}

void TreeItem::RemoveChildAt(int row)
{
    childItems.removeAt(row);
}

void TreeItem::SetActiveChunkName(QString &chunkName)
{
    activeChunkName = chunkName;
    activeChunk = &(itemData.dataChunks[activeChunkName]);
}

QVector<QVariant> TreeItem::GetChunkData(QString chunkName)
{
    return itemData.dataChunks[chunkName];
}

QVariant TreeItem::GetChunkDataElement(int column)
{
    return (*activeChunk)[column];
}

void TreeItem::SetChunkData(QString chunkName, QVector<QVariant> data)
{
    itemData.dataChunks[chunkName] = data;
}

void TreeItem::SetChunkDataElement(int column, QVariant data)
{
    (*activeChunk)[column] = data;
}

