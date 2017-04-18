#include "treeitem.h"
#include <QDebug>

TreeItem::TreeItem()
{
    parentItem = NULL;
    activeChunk = NULL;
}

TreeItem::TreeItem(TreeItem *parent, TreeItem *copy)
{
    parentItem = NULL;
    activeChunk = NULL;
    qDebug() << copy;
    parentItem = parent;
    if(!copy) return;
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
    qDebug() << "Add ITEM" << row << child << childItems.count();
}

void TreeItem::RemoveChild(TreeItem *child)
{
    childItems.removeOne(child);
}

void TreeItem::RemoveChildAt(int row)
{
    if(childItems.count() > row)
        childItems.removeAt(row);
}

void TreeItem::SetActiveChunkName(QString &chunkName)
{
    if(!itemData.dataChunks.contains(chunkName)) return;
    activeChunkName = chunkName;
    activeChunk = &(itemData.dataChunks[activeChunkName]);
}

QList<QString> TreeItem::GetChunksNames()
{
    return itemData.dataChunks.keys();
}

QVector<QVariant> TreeItem::GetChunkData(QString chunkName)
{
    return itemData.dataChunks[chunkName];
}

QVariant TreeItem::GetChunkDataElement(int column)
{
    if(!activeChunk) return QVariant();
    return (activeChunk->length() > column) ? (*activeChunk)[column] : QVariant();
}

void TreeItem::SetChunkData(QString chunkName, QVector<QVariant> data)
{
    itemData.dataChunks[chunkName] = data;
    if(activeChunkName == "")
        SetActiveChunkName(chunkName);

}

void TreeItem::SetChunkDataElement(int column, QVariant data)
{
    qDebug() << "SetChunkDataElement" << activeChunkName;
    if( (activeChunk->length() > column) || (column < 0) )
        (*activeChunk)[column] = data;
    else
        qDebug() << "Can't set column" << column;
}

