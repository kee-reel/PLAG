#include "item.h"

Item::Item()
{
    parentItem = nullptr;
    activeChunk = nullptr;
    id = -1;
}

Item::Item(Item *parent, Item *copy)
{
    parentItem = nullptr;
    activeChunk = nullptr;
    id = -1;
    parentItem = parent;

    if(!copy)
        return;

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
    if(!parentItem)
        return;

    parentItem->RemoveChild(this);
    parentItem = nullptr;
}

void Item::SetParent(Item *parent)
{
    parentItem = parent;
    dataChunks["tree"][0] = parent ? parent->GetId() : -1;
    dataChunks["tree"][1] = parent ? parent->GetChildPosition(this) : 0;
}

void Item::SetChilds(QList<Item *> childs)
{
    foreach (auto child, childs)
    {
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
    if(childItems.count() < row)
        return;

    Item *child = childItems[row];
    child->SetParent(nullptr);
    childItems.removeAt(row);
}

void Item::SetOneChunkActive(QString &chunkName)
{
    if(!dataChunks.contains(chunkName))
        return;

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

QVector<QVariant> Item::GetChunkData(QString chunkName) const
{
    if(chunkName == "")
        chunkName = activeChunkName;

    return dataChunks[chunkName];
}

QVariant Item::GetChunkDataElement(int column) const
{
    if(!activeChunk)
        return QVariant();

    return (activeChunk->length() > column) ? (*activeChunk)[column] : QVariant();
}

void Item::SetChunkData(QString chunkName, QVector<QVariant> data)
{
    dataChunks[chunkName] = data;

    if(activeChunkName == "")
        SetOneChunkActive(chunkName);
}

QVector<QVariant> Item::GetActiveChunksData() const
{
}

void Item::SetActiveChunksData(QVector<QVariant> data)
{
}

QMap<QString, QVariant> Item::GetChunksData() const
{
    QMap<QString, QVariant> result;
    auto iter = dataChunks.begin();

    while(iter != dataChunks.end())
    {
        result.insert(iter.key(), QVariant(iter.value().toList()) );
        ++iter;
    }

    return result;
}

void Item::SetChunksData(QMap<QString, QVariant> dataMap)
{
    auto iter = dataMap.begin();

    while(iter != dataMap.end())
    {
        if(!dataChunks.contains(iter.key()))
            qDebug() << "Adding a new data chunk in item:" << iter.key();

        QList<QVariant> dataList = iter.value().toList();
        dataChunks[iter.key()] = dataList.toVector();
        ++iter;
    }
}

void Item::SetChunkDataElement(int column, QVariant data)
{
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
