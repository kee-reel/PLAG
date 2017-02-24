#include "tasktreeitemmodel.h"


TaskTreeItemModel::TaskTreeItemModel(QString tableName,
                                     ITaskDataManagerPlugin* dataManager,
                                     QList<ITaskDataManagerPlugin::TaskInfo> &data,
                                     QObject *parent)
{
    this->tableName = tableName;
    this->dataManager = dataManager;

    QMap<int, TreeItem*> treeItemIdMap;
    QMap<int, QMap<int, TreeItem*>> treeItemParentMap;
    TreeItem *treeItem;
    ITaskDataManagerPlugin::TaskInfo *managerTaskData;
    for(int i = 0; i < data.count(); i++)
    {
        treeItem = new TreeItem();
        managerTaskData = &data[i];

        treeItem->SetId(managerTaskData->id);
        treeItem->SetData(1, managerTaskData->name);

        treeItemIdMap.insert(managerTaskData->id, treeItem);
        qDebug() << managerTaskData->id << managerTaskData->name << managerTaskData->position << managerTaskData->parent;

        if(data[i].parent == -1)
            rootItem = treeItem;
        else
        {
            qDebug() << "Child" << managerTaskData->parent << managerTaskData->position;
            treeItemParentMap[managerTaskData->parent].insert(managerTaskData->position, treeItem);
        }
    }
    QList<int> keys = treeItemParentMap.keys();
    for(int i = 0; i < keys.count(); i++)
    {
        TreeItem* parent = treeItemIdMap[keys[i]];
        qDebug() << "Childs" << keys[i] << treeItemParentMap[keys[i]].count() << "|";
        QList<TreeItem*> childItemsList = treeItemParentMap[keys[i]].values();
        for(int j = 0; j < childItemsList.count(); j++)
        {
           childItemsList[j]->parentItem = parent;
           qDebug() << "P" << childItemsList[j]->GetData(0) << parent->GetData(0);
        }
        parent->SetChilds(childItemsList);
    }

    QList<QVariant> testData;
    testData << QVariant("Name") << QVariant("Value");
    rootItem = new TreeItem(NULL, 0, testData);
    testData.clear();
    testData << QVariant("TeSt") << QVariant(12345);
    rootItem->AddChild(0, new TreeItem(rootItem, 1, testData));
    TreeItem *item = new TreeItem(rootItem, 2, testData);
    rootItem->AddChild(1, item);
    rootItem->AddChild(2, new TreeItem(rootItem, 3, testData));
    rootItem->AddChild(3, new TreeItem(rootItem, 4, testData));
    item->AddChild(1, new TreeItem(item, 5, testData));
    item->AddChild(2, new TreeItem(item, 6, testData));
    item->AddChild(3, new TreeItem(item, 7, testData));
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
        return item->GetData(index.column());
        break;
    case Qt::SizeHintRole:
        return QSize(0, 30);
        break;
    case Qt::ToolTipRole:
        return item->GetData(0);
        break;
    case Qt::FontRole:
        return QFont("Segoe UI", 14, QFont::Bold);
        break;
    case Qt::BackgroundRole:
        return QBrush(QColor(180 - index.row()*10, 180, 180));
        break;
    case Qt::EditRole:
        return item->GetData(index.column());
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
        return rootItem->GetData(section);
        break;
    case Qt::SizeHintRole:
        return QSize(0, 30);
        break;
    case Qt::ToolTipRole:
        return rootItem->GetData(0);
        break;
    case Qt::FontRole:
        return QFont("Segoe UI", 14, QFont::Bold);
        break;
    case Qt::BackgroundRole:
        return QBrush(QColor(180 - section*10, 180, 180));
        break;
    case Qt::EditRole:
        return rootItem->GetData(section);
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
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->GetChild(row);
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
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    return parentItem->ChildCount();
}

int TaskTreeItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

bool TaskTreeItemModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    if (!index.isValid())
        return false;



    //static_cast<TreeItem*>(index.internalPointer())->SetData(roles);
}

bool TaskTreeItemModel::insertRow(int row, const QModelIndex &parent)
{
//    TreeItem *parentItem;

//    if (!parent.isValid())
//        parentItem = rootItem;
//    else
//        parentItem = static_cast<TreeItem*>(parent.internalPointer());

//    TreeItem *childItem = parentItem->AddChild(row, );
//    if (childItem)
//        return createIndex(row, column, childItem);
//    else
    //        return QModelIndex();
}

bool TaskTreeItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData";
    if(!index.isValid())
        return false;

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    switch (role) {
    case Qt::EditRole:
        qDebug() << "!!!" << index.column() << value.toString();
        item->SetData(index.column(), value);
        //EditTask(item, value);
        break;
    default:
        break;
    }

    return true;
}

ITaskDataManagerPlugin::TaskInfo TaskTreeItemModel::ConvertToManagerTaskInfo(TreeItem* item)
{
    ITaskDataManagerPlugin::TaskInfo managerStruct;
    //Set id
    managerStruct.id = item->GetData(0).toInt();
    // Set name
    managerStruct.name = item->GetData(1).toString();
    // Set parent
    managerStruct.parent = item->parentItem ? item->parentItem->GetData(0).toInt() : -1;
    // Set position
    if(item->parentItem)
        managerStruct.position = item->parentItem->GetChildPosition(item);
    else
        managerStruct.position = 0;
    return managerStruct;
}

void TaskTreeItemModel::DeleteFromManagerRecursive(TreeItem *task)
{
    if(task->ChildCount() != 0)
        for(int i = 0; i < task->ChildCount(); i++)
            DeleteFromManagerRecursive(task->GetChild(i));

    dataManager->DeleteTask(tableName, task->GetData(0).toInt());
}

bool TaskTreeItemModel::AddTask(TreeItem *taskParent, TreeItem &taskData)
{
    qDebug() << "Add task";
    TreeItem *newTask = new TreeItem();
    newTask->SetData(1, taskData.GetData(1));
    qDebug() << taskParent;
    if(taskParent != NULL)
        taskParent->AddChild(taskParent->ChildCount(), newTask);
    newTask->parentItem = taskParent;

    ITaskDataManagerPlugin::TaskInfo managerTask = ConvertToManagerTaskInfo(newTask);
    qDebug() << managerTask.id << managerTask.name << managerTask.parent << managerTask.position;
    newTask->SetId(dataManager->AddTask(tableName, managerTask));
}

bool TaskTreeItemModel::EditTask(TreeItem *task, TreeItem taskData)
{
//    task->id = taskData.id;
//    task->name = taskData.name;

//    ITaskDataManagerPlugin::TaskInfo managerTask = ConvertToManagerTaskInfo(*task);
//    dataManager->EditTask(tableName, managerTask);
}

//bool TaskTreeItemModel::DeleteTask(ITaskTreeModel::TaskInfo *task)
//{
//    if(!task)
//        return false;
//    if(task->parent)
//        task->parent->childTasks.removeOne(task);
//    DeleteTaskRecursive(task);

//    dataManager->DeleteTask(tableName, task->id);
//}
