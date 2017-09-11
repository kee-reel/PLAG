#include "item.h"

Item::Item()
{
    parentItem = NULL;
    activeChunk = NULL;
    itemData.id = -1;
}

Item::Item(Item *parent, Item *copy)
{
    parentItem = NULL;
    activeChunk = NULL;
    itemData.id = -1;

    parentItem = parent;
    if(!copy) return;
    itemData.id = copy->itemData.id;
    itemData.dataChunks = copy->itemData.dataChunks;
    activeChunkName = copy->activeChunkName;
    activeChunk = &itemData.dataChunks[activeChunkName];
}

Item::Item(Item *parent, int id, QString chunkName, QMap<QString, QVector<QVariant>> dataChunks)
{
    parentItem = parent;
    itemData.id = id;
    itemData.dataChunks = dataChunks;
    activeChunkName = chunkName;
    activeChunk = &itemData.dataChunks[activeChunkName];
}

Item::~Item()
{
    if(childItems.count())
        for(int i = 0; i < childItems.count(); i++)
            delete childItems[i];
}

void Item::SetChilds(QList<Item *> childs)
{
    childItems = childs;
}

void Item::AddChild(int row, Item *child)
{
    childItems.insert(row, child);
    qDebug() << "Add ITEM" << row << child << childItems.count();
}

void Item::RemoveChild(Item *child)
{
    childItems.removeOne(child);
}

void Item::RemoveChildAt(int row)
{
    if(childItems.count() > row)
        childItems.removeAt(row);
}

void Item::SetActiveChunkName(QString &chunkName)
{
    if(!itemData.dataChunks.contains(chunkName)) return;
    activeChunkName = chunkName;
    activeChunk = &(itemData.dataChunks[activeChunkName]);
}

QList<QString> Item::GetChunksNames() const
{
    return itemData.dataChunks.keys();
}

QVariant Item::GetChunkName(int column) const
{
    if(column < itemData.dataChunks.count())
        return QVariant(itemData.dataChunks[activeChunkName].at(column));
    else
        return QVariant();
}

QVector<QVariant> Item::GetChunkData(QString chunkName)
{
    if(chunkName == "") chunkName = activeChunkName;
    return itemData.dataChunks[chunkName];
}

QVariant Item::GetChunkDataElement(int column)
{
    if(!activeChunk) return QVariant();
    return (activeChunk->length() > column) ? (*activeChunk)[column] : QVariant();
}

void Item::SetChunkData(QString chunkName, QVector<QVariant> data)
{
    itemData.dataChunks[chunkName] = data;
    if(activeChunkName == "")
        SetActiveChunkName(chunkName);
}

void Item::SetChunkDataElement(int column, QVariant data)
{
    qDebug() << "SetChunkDataElement" << activeChunkName;
    if( (activeChunk->length() > column) || (column < 0) )
        (*activeChunk)[column] = data;
    else
        qDebug() << "Can't set column" << column;
}

void Item::SetDecoration(QVariant pixmap)
{
    decoration = new QVariant(pixmap);
}

QVariant Item::GetDecoration()
{
    return *decoration;
}

