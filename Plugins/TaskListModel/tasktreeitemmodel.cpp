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

    QList<int> keys = treeItemParentMap.keys();
    for(int i = 0; i < keys.count(); i++)
    {
        TreeItem* parent = treeItemIdMap[keys[i]];
        QList<TreeItem*> childItemsList = treeItemParentMap[keys[i]].values();
        for(int j = 0; j < childItemsList.count(); j++)
        {
           childItemsList[j]->parentItem = parent;
           qDebug() << "Childs" << childItemsList[j]->GetId() << "->" << parent->GetId();
        }
        parent->SetChilds(childItemsList);
    }

    if(!rootItem)
    {
        rootItem = new TreeItem();
        QVector<QVariant> rootData;
        rootData << QVariant("Name");
        rootItem->SetChunkData(coreRelationName, rootData);
        rootItem->SetActiveChunkName(coreRelationName);
        AddTask(NULL, rootItem);
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
    case Qt::SizeHintRole:
        return QSize(0, 50);
        break;
    case Qt::ToolTipRole:
        return item->GetId();
        break;
    case Qt::FontRole:
        return QFont("Segoe UI", 20, QFont::Bold);
        break;
    case Qt::BackgroundRole:
        return QBrush(QColor(180 - index.row()*10, 180, 180));
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
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TaskTreeItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return rootItem->GetChunkDataElement(section);
        break;
    case Qt::SizeHintRole:
        return QSize(0, 30);
        break;
    case Qt::ToolTipRole:
        return rootItem->GetId();
        break;
    case Qt::FontRole:
        return QFont("Segoe UI", 14, QFont::Bold);
        break;
    case Qt::BackgroundRole:
        return QBrush(QColor(180 - section*10, 180, 180));
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
        qDebug() << "No Index";
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
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = AddTask(parentItem);
    endInsertRows();
}

bool TaskTreeItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count);
    TreeItem *parentItem;
    qDebug() << "removeRow";
    if (!parent.isValid())
        parentItem = rootItem;
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
        return false;

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    switch (role) {
    case Qt::EditRole:
        qDebug() << "!!!" << item->GetId() << index.column() << value.toString();
        EditTask(item, index.column(), value);
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

TreeItem *TaskTreeItemModel::AddTask(TreeItem *taskParent, TreeItem* taskData)
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
        taskParent->AddChild(taskParent->ChildCount(), newTask);

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
