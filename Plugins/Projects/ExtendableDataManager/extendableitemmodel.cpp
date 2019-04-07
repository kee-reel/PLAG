#include "extendableitemmodel.h"

ExtendableItemModel::ExtendableItemModel(QString tableName,
        IExtendableDataManager* dataManager,
        QObject *parent)
{
    this->tableName = tableName;
    this->dataManager = dataManager;
    coreRelationName = "tree";
    rootItem = nullptr;
}

ExtendableItemModel::~ExtendableItemModel()
{
    delete rootItem;
}

void ExtendableItemModel::LoadData()
{
    qDebug() << "Load data";

    rootItem = new Item(nullptr, &defaultTask);
    QMap<QString, QVariant::Type> newRelationStruct =
    {
        {"parent",      QVariant::Int},
        {"position",    QVariant::Int}
    };
    QVector<QVariant> defaultData = {-1, 0};
    dataManager->AddExtention(tableName, coreRelationName, newRelationStruct, defaultData);
    defaultTask.SetChunkData(coreRelationName, defaultData);
    QStringList relationFields = newRelationStruct.keys();
    parentIndex = relationFields.indexOf("parent");
    positionIndex = relationFields.indexOf("position");

    QList<ManagerDataItem> managerList = dataManager->GetDataList(tableName);
    // Item Id -> Item children.
    QMap<int, QMap<int, Item*>> internalTree;
    // Convert data manager list to internal list.
    QList<QString> chunksNames;

    if(managerList.count() > 0)
        chunksNames = managerList.first().dataChunks.keys();

    for(int i = 0; i < managerList.count(); i++)
    {
        Item *treeItem = new Item();
        ManagerDataItem *managerItemInfo = &managerList[i];
        treeItem->SetId(managerItemInfo->id);

        for(int chunksIter = 0; chunksIter < chunksNames.count(); ++chunksIter)
        {
            if(chunksNames[chunksIter] == coreRelationName)
            {
                QVector<QVariant> *dataChunk = &(managerItemInfo->dataChunks[coreRelationName]);
                internalTree[dataChunk->at(parentIndex).toInt()].insertMulti(dataChunk->at(positionIndex).toInt(), treeItem);
            }

            treeItem->SetChunkData(chunksNames[chunksIter], managerItemInfo->dataChunks[chunksNames[chunksIter]]);
        }

        internalList.insert(managerItemInfo->id, treeItem);
    }

    // Link list to tree
    QList<int> keys = internalTree.keys();

    for(int i = 0; i < keys.count(); i++)
    {
        Item* parent = (internalList.contains(keys[i])) ? internalList[keys[i]] : rootItem;
        QList<Item*> childItemsList = internalTree[keys[i]].values();
        parent->SetChilds(childItemsList);
    }
}

bool ExtendableItemModel::AttachRelation(QString relationName, TableStructMap fields, QVector<QVariant> defaultData)
{
    defaultTask.SetChunkData(relationName, defaultData);
    auto list = fields.keys();
    QVector<QVariant> varList;
    QVector<QVariant> emptyData;

    foreach (auto elem, list)
        varList.append(QVariant(elem));

    emptyData.resize(list.length());
    header.SetChunkData(relationName, varList);

    if(!dataTypeEditors.HasChunk(relationName))
        dataTypeEditors.SetChunkData(relationName, emptyData);

    return true;
}

void ExtendableItemModel::SetActiveRelation(QString relationName)
{
    qDebug() << "===SetActiveRelation===" << relationName;
    QList<Item*> keys = internalList.values();

    for(int i = 0; i < keys.count(); ++i)
        keys[i]->SetOneChunkActive(relationName);

    currentActiveChunkName = relationName;
    defaultTask.SetOneChunkActive(relationName);
    header.SetOneChunkActive(relationName);
}

void ExtendableItemModel::SetDataTypeEditor(QString dataChunk, QString fieldName, QWidget *widget)
{
    QVector<QVariant> data = dataTypeEditors.GetChunkData(dataChunk);
    auto chunkHeader = header.GetChunkData(dataChunk);

    if(data.length() == 0)
        data.resize(chunkHeader.length());

    for(int i = 0; i < chunkHeader.length(); ++i)
    {
        if(chunkHeader[i] == fieldName)
            data[i] = QVariant::fromValue((void*)widget);
    }

    dataTypeEditors.SetChunkData(dataChunk, data);
}

QVariant ExtendableItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Item *item = static_cast<Item*>(index.internalPointer());

    switch (role)
    {
        case Qt::DisplayRole:
            return item->GetChunkDataElement(index.column());
            break;

        case Qt::EditRole:
            return item->GetChunkDataElement(index.column());
            break;

        //    case Qt::DecorationRole:
        //        qDebug() << "Get DecorationRole";
        //        return item->GetDecoration();
        //        break;
        default:
            return QVariant();
            break;
    }
}

QMap<QString, QVariant> ExtendableItemModel::ConvertToHeadedMap(QMap<QString, QVariant> headerMap, QMap<QString, QVariant> valuesMap) const
{
    QMap<QString, QVariant> chunksMap;
    auto valuesNamesIter = headerMap.begin();
    auto valuesIter = valuesMap.begin();

    while(valuesNamesIter != headerMap.end() || valuesIter != valuesMap.end())
    {
        QString chunkName = valuesNamesIter.key();
        QList<QVariant> valuesNamesList = valuesNamesIter.value().toList();
        QList<QVariant> valuesList = valuesIter.value().toList();

        if(valuesNamesList.length() == valuesList.length())
        {
            QMap<QString, QVariant> headedValuesMap;

            for(int i = 0; i < valuesNamesList.length(); ++i)
                headedValuesMap.insert(valuesNamesList[i].toString(), valuesList[i]);

            chunksMap.insert(chunkName, QVariant(headedValuesMap));
        }
        else
        {
            qWarning() << "Chunk" << chunkName << "is corrupted";
        }

        ++valuesNamesIter;
        ++valuesIter;
    }

    return chunksMap;
}

QMap<int, QVariant> ExtendableItemModel::itemData(const QModelIndex &index) const
{
    if (!index.isValid())
        return QMap<int, QVariant>();

    QMap<int, QVariant> result;
    Item *item = static_cast<Item*>(index.internalPointer());
    auto headerMap = header.GetChunksData();
    auto valuesMap = item->GetChunksData();
    // Because for which reason internal data could be needed by user?
    headerMap.remove(coreRelationName);
    valuesMap.remove(coreRelationName);
    QMap<QString, QVariant> chunksMap = ConvertToHeadedMap(headerMap, valuesMap);
    result.insert(Qt::UserRole, QVariant(chunksMap));
    return result;
}

QMap<QString, QVariant> ExtendableItemModel::ConvertFromHeadedMap(QMap<QString, QVariant> dataMap)
{
    QMap<QString, QVariant> convertedMap;
    auto iter = dataMap.begin();

    while(iter != dataMap.end())
    {
        auto headedValuesMap = iter.value().toMap();
        QList<QVariant> dataList = headedValuesMap.values();
        convertedMap.insert(iter.key(), QVariant(dataList));
        ++iter;
    }

    return convertedMap;
}

bool ExtendableItemModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    if (!index.isValid())
        return false;

    if(!roles.contains(Qt::UserRole))
        return QAbstractItemModel::setItemData(index, roles);

    Item *item = static_cast<Item*>(index.internalPointer());

    if(item == nullptr)
        return false;

    QMap<QString, QVariant> dataMap = roles[Qt::UserRole].toMap();
    QMap<QString, QVariant> convertedMap = ConvertFromHeadedMap(dataMap);
    item->SetChunksData(convertedMap);
    UpdateItem(item);
    //    emit dataChanged(index, index);
    return QAbstractItemModel::setItemData(index, roles);
}

Qt::ItemFlags ExtendableItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags | Qt::ItemIsDropEnabled;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QVariant ExtendableItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
        case Qt::DisplayRole:
            return header.GetChunkName(section);
            break;

        case Qt::ToolTipRole:
            return rootItem->GetId();
            break;

        case Qt::EditRole:
            return rootItem->GetChunkDataElement(section);
            break;

        case Qt::UserRole:
        {
            auto headerMap = header.GetChunksData();
            auto valuesMap = dataTypeEditors.GetChunksData();
            // Because for which reason internal data could be needed by user?
            headerMap.remove(coreRelationName);
            valuesMap.remove(coreRelationName);
            QMap<QString, QVariant> dataEditorsMap = ConvertToHeadedMap(headerMap, valuesMap);
            return QVariant(dataEditorsMap);
        } break;

        default:
            return QVariant();
            break;
    }

    return QVariant();
}

QModelIndex ExtendableItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        qDebug() << "No Index for" << row << column << parent;
        return QModelIndex();
    }

    Item *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<Item*>(parent.internalPointer());

    Item *childItem = parentItem->GetChildAt(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ExtendableItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Item *childItem = static_cast<Item*>(index.internalPointer());

    if (childItem->ParentIsRoot() || !childItem->HasParent())
        return QModelIndex();

    Item *parentItem = childItem->GetParent();
    return createIndex(parentItem->GetRow(), 0, parentItem);
}

int ExtendableItemModel::rowCount(const QModelIndex &parent) const
{
    Item *parentItem;
    parentItem = (!parent.isValid()) ? rootItem : static_cast<Item*>(parent.internalPointer());
    return parentItem->ChildCount();
}

int ExtendableItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<Item*>(parent.internalPointer())->ColumnCount();
    else
        return rootItem->ColumnCount();
}

bool ExtendableItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Item *parentItem;
    parentItem = (!parent.isValid()) ? rootItem : static_cast<Item*>(parent.internalPointer());

    if(row == -1 || row >= parentItem->ChildCount())
        row = parentItem->ChildCount();

    beginInsertRows(parent, row, row+count);
    Item *childItem = AddItem(row, parentItem);
    endInsertRows();
    return true;
}

bool ExtendableItemModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    return true;
}

bool ExtendableItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count);
    Item *parentItem;
    parentItem = (!parent.isValid()) ? rootItem : static_cast<Item*>(parent.internalPointer());
    Item *item = parentItem->GetChildAt(row);

    if(item)
        DeleteItem(item);

    endRemoveRows();
    return true;
}

bool ExtendableItemModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent,
                                   int destinationChild)
{
    qDebug() << "moveRows" << sourceParent << sourceRow << count << destinationParent << destinationChild;
    int sourceLast = sourceRow+count;
    Item *sourceParentItem = (!sourceParent.isValid()) ? rootItem : static_cast<Item*>(sourceParent.internalPointer());
    Item *destinationParentItem = (!destinationParent.isValid()) ? rootItem : static_cast<Item*>(destinationParent.internalPointer());
    Item *destinationChildItem = destinationParentItem->GetChildAt(destinationChild);
    qDebug() << sourceParentItem << destinationChildItem << destinationParentItem->ChildCount() << sourceParentItem->ChildCount();
    QList<Item*> movingItems;

    if(!beginMoveRows(sourceParent, sourceRow, sourceLast, destinationParent, destinationChild))
    {
        qDebug() << "Wrong move";
        return false;
    }

    for(int i = sourceRow; i <= sourceLast; ++i)
    {
        movingItems.append(sourceParentItem->GetChildAt(i));
        //        sourceParentItem->RemoveChildAt(i);
        //        destinationParentItem->AddChild(movingItems.last());
    }

    destinationChild = destinationChildItem ? destinationChildItem->GetRow() : destinationChild;

    for(int i = 0; i < movingItems.count(); ++i)
    {
        sourceParentItem->RemoveChild(movingItems[i]);
        destinationParentItem->AddChild(movingItems[i], destinationChild);
    }

    endMoveRows();
    return true;
}

bool ExtendableItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData" << index.row() << index.column() << index.data() << value;
    Item *item = (!index.isValid()) ? rootItem : static_cast<Item*>(index.internalPointer());

    switch (role)
    {
        case Qt::EditRole:
            item->SetChunkDataElement(index.column(), value);
            UpdateItem(item);
            emit dataChanged(index, index);
            break;

        //    case Qt::DecorationRole:
        //        qDebug() << "Set DecorationRole";
        //        item->SetDecoration(value);
        //        break;
        default:
            break;
    }

    return true;
}

QStringList ExtendableItemModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}

QMimeData *ExtendableItemModel::mimeData(const QModelIndexList &indexes) const
{
    qDebug() << "mimeData" << indexes.count();
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    stream << (quintptr)this;

    foreach (const QModelIndex &index, indexes)
    {
        if (index.isValid())
        {
            int row = index.row();
            int column = index.column();
            quintptr indexPtr = (quintptr)index.internalPointer();
            quintptr parentPtr = (quintptr)index.parent().internalPointer();
            qDebug() << row << column << indexPtr << parentPtr;
            stream << row << column << indexPtr << parentPtr;
        }
    }

    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}

bool ExtendableItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qDebug() << "dropMimeData" << row << column << parent;

    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("application/vnd.text.list"))
        return false;

    if (column > 0)
        return false;

    int beginRow;

    if (row != -1)
        beginRow = row;
    else if (parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());

    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    qintptr modelPtr = reinterpret_cast<qintptr>(nullptr);
    stream >> modelPtr;
    QMap<quintptr, QMap<int, quintptr>> newItems;
    int rows = 0;

    while (!stream.atEnd())
    {
        int row;
        int column;
        quintptr idxPtr;
        quintptr parentPtr;
        stream >> row;
        stream >> column;
        stream >> idxPtr;
        stream >> parentPtr;
        qDebug() << row << column << idxPtr << parentPtr;
        newItems[parentPtr][row] = idxPtr;
        qDebug() << newItems.count();
        ++rows;
    }

    if(modelPtr == (qintptr)this)
    {
        ReadSameModelMime(beginRow, row, parent, newItems);
    }
    else
    {
        qDebug() << "!Another model!";
        return false;
    }

    return true;
}

void ExtendableItemModel::ReadSameModelMime(int beginRow, int row, const QModelIndex &parent, QMap<quintptr, QMap<int, quintptr>> &newItems)
{
    QModelIndex bufIdx;
    QModelIndex blockFirstIdx;
    QModelIndex parentIdx;
    Item *blockFirstItem;

    if(!parent.isValid())
    {
        parentIdx = createIndex(-1, -1, newItems.begin().key());
        qDebug() << "That's it!";
    }
    else
        parentIdx = parent;

    QMap<quintptr, QMap<int, quintptr>>::Iterator parentI = newItems.begin();

    while(parentI != newItems.end())
    {
        qDebug() << "parentI" << parentI.key();
        QMap<int, quintptr> rows = parentI.value();
        QMap<int, quintptr>::Iterator rowsI = rows.begin();
        QMap<int, quintptr>::Iterator lastRowI = --rows.end();
        int itemsBlock = 0;
        int prevRow = -1;
        blockFirstItem = nullptr;

        while(rowsI != rows.end())
        {
            qDebug() << "rowsI" << rowsI.key();
            bufIdx = createIndex(rowsI.key(), 0, rowsI.value());

            if(itemsBlock == 0)
                blockFirstIdx = bufIdx;

            if( prevRow != -1 && (prevRow != rowsI.key()-1) )
            {
                qDebug() << "Second";
                Item *treeItem = (Item*)blockFirstIdx.internalPointer();
                moveRows(blockFirstIdx.parent(), treeItem->GetRow(), itemsBlock-1, parentIdx, beginRow);
                blockFirstIdx = bufIdx;
                itemsBlock = 0;
            }

            if(rowsI == lastRowI)
            {
                qDebug() << "First";
                Item *treeItem = (Item*)blockFirstIdx.internalPointer();
                moveRows(blockFirstIdx.parent(), treeItem->GetRow(), itemsBlock, parentIdx, beginRow);
                itemsBlock = 0;
            }

            prevRow = rowsI.key();
            ++itemsBlock;
            ++rowsI;
        }

        UpdateItemsPosition((Item*)parentI.key(), rows.begin().key());
        ++parentI;
    }

    UpdateItemsPosition((Item*)parent.internalPointer(), (row == -1) ? 0 : row);
}

Item *ExtendableItemModel::AddItem(int row, Item *taskParent, Item* taskData)
{
    if(!dataManager)
    {
        qDebug() << "Data manager not set!";
        return nullptr;
    }

    if(!taskParent)
        taskParent = rootItem;

    if(!taskData)
        taskData = &defaultTask;

    qDebug() << "Add task";
    Item *newTask = new Item(taskParent, taskData);

    if(taskParent)
        taskParent->AddChild(newTask, row);

    int newTaskId = dataManager->AddItem(tableName, *newTask);
    newTask->SetId(newTaskId);
    newTask->SetOneChunkActive(currentActiveChunkName);
    internalList.insert(newTaskId, newTask);
    return newTask;
}

bool ExtendableItemModel::UpdateItem(Item *task)
{
    qDebug() << "EditTask";

    if(!dataManager)
    {
        qDebug() << "Data manager not set!";
        return false;
    }

    dataManager->UpdateItem(tableName, *task);
}

bool ExtendableItemModel::UpdateItemsPosition(Item *parent, int from)
{
    if(!dataManager)
    {
        qDebug() << "Data manager not set!";
        return false;
    }

    if(!parent)
        parent = rootItem;

    int to = parent->ChildCount();
    qDebug() << "UpdateTaskPositions" << parent << parent->GetChunkDataElement(0) << from;

    for(int i = from; i < to; ++i)
    {
        qDebug() << parent->ChildCount() << to;
        qDebug() << parent->ChildCount() << parent->GetChildAt(i);
        dataManager->UpdateItem(tableName, *(parent->GetChildAt(i)));
    }
}

bool ExtendableItemModel::DeleteItem(Item *task)
{
    qDebug() << "DeleteTask";

    if(!dataManager)
    {
        qDebug() << "Data manager not set!";
        return false;
    }

    if(!task)
        return false;

    task->DetachFromParent();
    DeleteFromManagerRecursive(task);
}

//IExtendableDataManager::ManagerDataItem ExtendableItemModel::ConvertToManagerItem(Item* item)
//{
//    ManagerDataItem managerStruct;
//    // Set id
//    managerStruct.id = item->GetId();
//    QStringList list = item->GetChunksNames();
//    for(int i = 0; i < list.count(); ++i)
//        managerStruct.dataChunks[list[i]] = item->GetChunkData(list[i]);

//    // Set parent
//    managerStruct.dataChunks[coreRelationName].append(item->parentItem ? item->parentItem->GetId() : -1);
//    // Set position
//    managerStruct.dataChunks[coreRelationName].append((item->parentItem) ? item->parentItem->GetChildPosition(item) : 0);
//    return managerStruct;
//}

void ExtendableItemModel::DeleteFromManagerRecursive(Item *task)
{
    if(task->ChildCount() != 0)
        for(int i = 0; i < task->ChildCount(); i++)
            DeleteFromManagerRecursive(task->GetChildAt(i));

    internalList.remove(task->GetId());
    dataManager->DeleteItem(tableName, task->GetId());
}
