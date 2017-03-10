#include "tasktreeitemmodel.h"


TaskTreeItemModel::TaskTreeItemModel(QString tableName,
                                     IExtendableDataBaseManagerPlugin* dataManager,
                                     QObject *parent)
{
    this->tableName = tableName;
    this->dataManager = dataManager;
    coreRelationName = "tree";\
    rootItem = NULL;

    QMap<QString, QVariant::Type> newRelationStruct = {
        {"name",        QVariant::String},
        {"parent",      QVariant::Int},
        {"position",    QVariant::Int}
    };
    dataManager->SetRelation(tableName, coreRelationName, newRelationStruct);

    QStringList relationFields = newRelationStruct.keys();
    nameIndex = relationFields.indexOf("name");
    parentIndex = relationFields.indexOf("parent");
    positionIndex = relationFields.indexOf("position");

    qDebug() << nameIndex << parentIndex << positionIndex;

    QMap<int, TreeItem*> treeItemIdMap;
    QMap<int, QMap<int, TreeItem*>> treeItemParentMap;

    TreeItem *treeItem;
    QVector<QVariant> *dataChunk;
    QList<ManagerItemInfo> data = dataManager->GetData(tableName);

    ManagerItemInfo *managerTaskData;
    for(int i = 0; i < data.count(); i++)
    {
        treeItem = new TreeItem();
        managerTaskData = &data[i];
        dataChunk = &(data[i].dataChunks[coreRelationName]);

        qDebug() << "New task"
                    << managerTaskData->id
                        << dataChunk->at(nameIndex)
                            << dataChunk->at(parentIndex)
                                << dataChunk->at(positionIndex);

        treeItemIdMap.insert(managerTaskData->id, treeItem);
        qDebug() << managerTaskData->id << dataChunk->at(positionIndex) << dataChunk->at(parentIndex);

        if(dataChunk->at(parentIndex).toInt() == -1)
        {
            rootItem = treeItem;
        }
        else
        {
            qDebug() << "Child" << dataChunk->at(parentIndex) << dataChunk->at(positionIndex);
            treeItemParentMap[dataChunk->at(parentIndex).toInt()].insert(dataChunk->at(positionIndex).toInt(), treeItem);
        }

        treeItem->SetId(managerTaskData->id);
        dataChunk->removeLast();
        dataChunk->removeLast();
        treeItem->SetChunkData(coreRelationName, *dataChunk);
        treeItem->SetActiveChunkName(coreRelationName);
    }

    if(!rootItem)
    {
        qDebug() << "Root is empty";
        rootItem = new TreeItem();
        QVector<QVariant> rootData;
        rootData << QVariant("Name");
        rootItem->SetChunkData(coreRelationName, rootData);
        rootItem->SetActiveChunkName(coreRelationName);
        AddTask(NULL, rootItem);
    }

    QList<int> keys = treeItemParentMap.keys();
    for(int i = 0; i < keys.count(); i++)
    {
        TreeItem* parent = treeItemIdMap[keys[i]];
        if(!parent)
            parent = rootItem;
        QList<TreeItem*> childItemsList = treeItemParentMap[keys[i]].values();
        qDebug() << "Parent" << parent->GetId() << "Childs" << childItemsList.count();
        for(int j = 0; j < childItemsList.count(); j++)
        {
           childItemsList[j]->parentItem = parent;
           qDebug() << "Childs" << childItemsList[j]->GetId() << "->" << parent->GetId();
        }
        parent->SetChilds(childItemsList);
    }

    QVector<QVariant> defaultData;
    defaultData << QVariant("New task") << QVariant(1) << QVariant(0);
    defaultTask.SetChunkData(coreRelationName, defaultData);
    defaultTask.SetActiveChunkName(coreRelationName);
}

TaskTreeItemModel::~TaskTreeItemModel()
{
    delete rootItem;
}

QVariant TaskTreeItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    switch (role) {
    case Qt::DisplayRole:
        return item->GetChunkDataElement(index.column());
        break;
    case Qt::ToolTipRole:
        return item->GetId();
        break;
    case Qt::EditRole:
        return item->GetChunkDataElement(index.column());
        break;
    default:
        return QVariant();
        break;
    }

}

Qt::ItemFlags TaskTreeItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags | Qt::ItemIsDropEnabled;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QVariant TaskTreeItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return rootItem->GetChunkDataElement(section);
        break;
    case Qt::ToolTipRole:
        return rootItem->GetId();
        break;
    case Qt::EditRole:
        return rootItem->GetChunkDataElement(section);
        break;
    default:
        return QVariant();
        break;
    }

    return QVariant();
}

QModelIndex TaskTreeItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        qDebug() << "No Index for" << row << column << parent;
        return QModelIndex();
    }

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->GetChildAt(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TaskTreeItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem;

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->GetRow(), 0, parentItem);
}

int TaskTreeItemModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    return parentItem->ChildCount();
}

int TaskTreeItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->ColumnCount();
    else
        return rootItem->ColumnCount();
}

bool TaskTreeItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count);
    TreeItem *parentItem;
    qDebug() << "insertRow";
    if (!parent.isValid())
    {
        qDebug() << "!!!!!";
        parentItem = rootItem;
    }
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = AddTask(row, parentItem);
    endInsertRows();
}

bool TaskTreeItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count);
    TreeItem *parentItem;
    qDebug() << "removeRow";
    if (!parent.isValid())
    {
        parentItem = rootItem;
    }
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *item = parentItem->GetChildAt(row);
    if(item)
        DeleteTask(item);
    endRemoveRows();
}

bool TaskTreeItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData";
    if(!index.isValid())
    {
        qDebug() << index.row() << index.column() << index.data() << value.toString();
        return false;
    }

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    switch (role) {
    case Qt::EditRole:
        qDebug() << "!!!" << item->GetId() << index.column() << value.toString();
        EditTask(item, index.column(), value);
        emit dataChanged(index, index);
        break;
    default:
        break;
    }

    return true;
}

IExtendableDataBaseManagerPlugin::ManagerItemInfo TaskTreeItemModel::ConvertToManagerTaskInfo(TreeItem* item)
{
    ManagerItemInfo managerStruct;
    //Set id
    managerStruct.id = item->GetId();
    // Set name
    managerStruct.dataChunks[coreRelationName].append(item->GetChunkDataElement(0));
    // Set parent
    managerStruct.dataChunks[coreRelationName].append(item->parentItem ? item->parentItem->GetId() : -1);
    // Set position
    managerStruct.dataChunks[coreRelationName].append((item->parentItem) ? item->parentItem->GetChildPosition(item) : 0);
    return managerStruct;
}

void TaskTreeItemModel::DeleteFromManagerRecursive(TreeItem *task)
{
    if(task->ChildCount() != 0)
        for(int i = 0; i < task->ChildCount(); i++)
            DeleteFromManagerRecursive(task->GetChildAt(i));

    dataManager->DeleteItem(tableName, task->GetId());
}

TreeItem *TaskTreeItemModel::AddTask(int row, TreeItem *taskParent, TreeItem* taskData)
{
    if(!dataManager)
    {
        qDebug() << "Data manager not set!";
        return false;
    }
    if(taskData == NULL)
    {
        taskData = &defaultTask;
    }

    qDebug() << "Add task";
    TreeItem *newTask = new TreeItem(taskParent, taskData);
    qDebug() << taskParent;
    if(taskParent != NULL)
        taskParent->AddChild(row, newTask);

    ManagerItemInfo managerTask = ConvertToManagerTaskInfo(newTask);
    int newTaskId = dataManager->AddItem(tableName, managerTask);
    qDebug() << newTaskId;
    newTask->SetId(newTaskId);
}

bool TaskTreeItemModel::EditTask(TreeItem *task, int column, QVariant dataField)
{
    qDebug() << "EditTask";
    task->SetChunkDataElement(column, dataField);
    if(!dataManager)
    {
        qDebug() << "Data manager not set!";
        return false;
    }
    ManagerItemInfo managerTask = ConvertToManagerTaskInfo(task);
    dataManager->EditItem(tableName, managerTask);
}

bool TaskTreeItemModel::DeleteTask(TreeItem *task)
{
    qDebug() << "DeleteTask";
    if(!dataManager)
    {
        qDebug() << "Data manager not set!";
        return false;
    }
    if(!task)
        return false;
    if(task->parentItem)
        task->parentItem->RemoveChild(task);
    DeleteFromManagerRecursive(task);
    qDebug() << "DeleteTask1";
}

QStringList TaskTreeItemModel::mimeTypes() const
{
    qDebug() << "mimeTypes";
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}

QMimeData *TaskTreeItemModel::mimeData(const QModelIndexList &indexes) const
{
    qDebug() << "mimeData" << indexes.count();
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            int row = index.row();
            int column = index.column();
            quintptr parent = (quintptr)index.internalPointer();
            qDebug() << "Pointer" << parent << index.internalPointer();
            QString text = data(index, Qt::DisplayRole).toString();
            qDebug() << row << column << parent << text;
            stream << row << column << parent << text;
        }
    }

    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}

bool TaskTreeItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qDebug() << "dropMimeData";
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
    QList< QVector<QVariant> >  newItems;
    int rows = 0;

    while (!stream.atEnd()) {
        newItems.append( QVector<QVariant>() );
        newItems[rows].resize(4);
        int row;
        int column;
        quintptr parent;
        QString text;
        stream >> row;
        stream >> column;
        stream >> parent;
        stream >> text;
        qDebug() << row << column << parent << text;
        newItems[rows][0] = row;
        newItems[rows][1] = column;
        newItems[rows][2] = parent;
        newItems[rows][3] = text;
        ++rows;
    }

//    for(int i = 0; i < newItems.count(); i++) {
//        qDebug() << "X";
//        QModelIndex previdx = createIndex(newItems[i][0].toInt(), newItems[i][1].toInt(), newItems[i][2].toUInt());
//        qDebug() << previdx.internalId() << previdx.internalPointer();
//    }

    for(int i = 0; i < newItems.count(); i++) {
        QModelIndex idx = index(beginRow, 0, parent);
        QModelIndex previdx = createIndex(newItems[i][0].toInt(), newItems[i][1].toInt(), newItems[i][2].toUInt());
        if(!previdx.isValid())
        {
            qDebug() << "previdx is empty";
            continue;
        }
        qDebug() << "RM" << previdx.data();
        removeRows(previdx.row(), 1, previdx.parent());
        insertRows(parent.row()+i, 1, parent.parent());
        setData(index(parent.row()+i, 0, parent.parent()), newItems[i][3], Qt::EditRole);


        beginRow++;
    }

    return true;
}

bool TaskTreeItemModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    qDebug() << "moveRows";
}
