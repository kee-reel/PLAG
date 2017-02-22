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

        treeItem->SetData(0, managerTaskData->id);
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
    testData << QVariant(777) << QVariant("TeSt");
    rootItem = new TreeItem(NULL, testData);
    rootItem->AddChild(0, new TreeItem(rootItem, testData));
    TreeItem *item = new TreeItem(rootItem, testData);
    rootItem->AddChild(1, item);
    rootItem->AddChild(2, new TreeItem(rootItem, testData));
    rootItem->AddChild(3, new TreeItem(rootItem, testData));
    item->AddChild(1, new TreeItem(item, testData));
    item->AddChild(2, new TreeItem(item, testData));
    item->AddChild(3, new TreeItem(item, testData));
}

TaskTreeItemModel::~TaskTreeItemModel()
{
    delete rootItem;
}

QVariant TaskTreeItemModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "data";
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
    default:
        return QVariant();
        break;
    }

}

Qt::ItemFlags TaskTreeItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant TaskTreeItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
//    qDebug() << "headerData" << rootItem;
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        return rootItem->GetData(section);

    return QVariant();
}

QModelIndex TaskTreeItemModel::index(int row, int column, const QModelIndex &parent) const
{
    qDebug() << "index";
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
    qDebug() << "parent";
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
    qDebug() << "rowCount";
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    qDebug() << parentItem;
    return parentItem->ChildCount();
}

int TaskTreeItemModel::columnCount(const QModelIndex &parent) const
{
    qDebug() << "columnCount";
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

bool TaskTreeItemModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    qDebug() << "setItemData";
//    if (!index.isValid())
//        return false;
//    static_cast<TreeItem*>(index.internalPointer())->SetName(roles);
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
    if(!index.isValid())
        return false;

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    item->SetData(index.column(), value);
    //EditTask(item, value);

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
    newTask->SetData(0, dataManager->AddTask(tableName, managerTask));
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
