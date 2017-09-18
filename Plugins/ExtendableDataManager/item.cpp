#include "item.h"

Item::Item()
{
    parentItem = NULL;
    activeChunk = NULL;
    id = -1;
}

Item::Item(Item *parent, Item *copy)
{
    parentItem = NULL;
    activeChunk = NULL;
    id = -1;

    parentItem = parent;
    if(!copy) return;
    id = copy->id;
    dataChunks = copy->dataChunks;
    activeChunkName = copy->activeChunkName;
    activeChunk = &dataChunks[activeChunkName];
}

Item::Item(Item *parent, int id, QString chunkName, QMap<QString, QVector<QVariant>> dataChunks)
{
    parentItem = parent;
    id = id;
    this->dataChunks = dataChunks;
    activeChunkName = chunkName;
    activeChunk = &(this->dataChunks[activeChunkName]);
}

Item::~Item()
{
    if(childItems.count())
        for(int i = 0; i < childItems.count(); i++)
            delete childItems[i];
}

void Item::DetachFromParent()
{
    if(!parentItem) return;
    parentItem->RemoveChild(this);
    parentItem = NULL;
}

void Item::SetParent(Item *parent)
{
    parentItem = parent;
    dataChunks["tree"][0] = parent ? parent->GetId() : -1;
    dataChunks["tree"][1] = parent ? parent->GetChildPosition(this) : 0;
}

void Item::SetChilds(QList<Item *> childs)
{
    foreach (auto child, childs) {
        AddChild(child, childItems.count());
    }
}

void Item::AddChild(Item *child, int row)
{
    childItems.insert(row, child);
    child->SetParent(this);
}

void Item::RemoveChild(Item *child)
{
    childItems.removeOne(child);
}

void Item::RemoveChildAt(int row)
{
    if(childItems.count() < row) return;
    Item *child = childItems[row];
    child->SetParent(NULL);
    childItems.removeAt(row);
}

void Item::SetOneChunkActive(QString &chunkName)
{
    if(!dataChunks.contains(chunkName)) return;
    activeChunkName = chunkName;
    activeChunk = &(dataChunks[activeChunkName]);
}

void Item::ToggleChunkActive(QString &activeChunk)
{

}

void Item::ToggleAllChunksActive(QString &activeChunk)
{

}

QList<QString> Item::GetChunksNames() const
{
    return dataChunks.keys();
}

QVariant Item::GetChunkName(int column) const
{
    if(column < dataChunks.count())
        return QVariant(dataChunks[activeChunkName].at(column));
    else
        return QVariant();
}

QVector<QVariant> Item::GetChunkData(QString chunkName)
{
    if(chunkName == "") chunkName = activeChunkName;
    return dataChunks[chunkName];
}

QVariant Item::GetChunkDataElement(int column)
{
    if(!activeChunk) return QVariant();
    return (activeChunk->length() > column) ? (*activeChunk)[column] : QVariant();
}

void Item::SetChunkData(QString chunkName, QVector<QVariant> data)
{
    dataChunks[chunkName] = data;
    if(activeChunkName == "")
        SetOneChunkActive(chunkName);
}

QVector<QVariant> Item::GetActiveChunksData()
{

}

void Item::SetActiveChunksData(QVector<QVariant> data)
{

}

QMap<int, QVariant> Item::GetAllChunksData()
{
    QMap<int, QVariant> result;
    auto chunkNames = dataChunks.keys();
    foreach (auto chunkName, chunkNames) {
        auto values = dataChunks[chunkName];
        int flag = (chunkName == activeChunkName) ? 1 : 0;
        result.insertMulti(flag, QVariant(values.toList()));
    }
    return result;
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
