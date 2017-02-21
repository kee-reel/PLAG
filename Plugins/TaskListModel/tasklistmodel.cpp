#include "tasklistmodel.h"

TaskListModel::TaskListModel()
{
    activeViewId = -1;
    rootTask = NULL;
}

TaskListModel::~TaskListModel()
{
}

void TaskListModel::AddChildPlugin(IPluginModel *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IPluginModel> newPlugin = {plugin, meta};
    childModelPlugins.append(newPlugin);
}

void TaskListModel::SetDataManager(QObject *DBTool)
{
    this->dataManager = qobject_cast<ITaskDataManagerPlugin*>(DBTool);
    if(!this->dataManager)
    {
        qDebug() << DBTool->objectName() << "is not ITaskDBToolPlugin.";
        return;
    }
    qDebug() << "ITaskDBToolPlugin succesfully set.";
}

QString TaskListModel::GetError()
{

}

ITaskListModel::TaskInfo *TaskListModel::GetRootTask()
{
    QList<ITaskDataManagerPlugin::TaskInfo> managerTaskList = dataManager->GetTaskTree(tableName);
    if(managerTaskList.count() == 0)
    {
        qDebug() << "Tree is empty";
        return NULL;
    }
    QMap<int, ITaskListModel::TaskInfo*> taskMap;
    QMap<int, QMap<int, ITaskListModel::TaskInfo*>> taskParentMap;
    ITaskListModel::TaskInfo *task;
    ITaskDataManagerPlugin::TaskInfo *managerTask;
    qDebug() << "1";
    for(int i = 0; i < managerTaskList.count(); i++)
    {
        task = new ITaskListModel::TaskInfo();
        managerTask = &managerTaskList[i];
        task->id = managerTask->id;
        task->name = managerTask->name;
        task->parent = NULL;
        taskMap.insert(task->id, task);
        qDebug() << managerTask->id << managerTask->name << managerTask->position << managerTask->parent;

        if(managerTaskList[i].parent == -1)
            rootTask = task;
        else
        {
            qDebug() << "Child" << managerTask->parent << managerTask->position;
            taskParentMap[managerTask->parent].insert(managerTask->position, task);
        }
    }

    QList<int> keys = taskParentMap.keys();
    for(int i = 0; i < keys.count(); i++)
    {
        ITaskListModel::TaskInfo* parent = taskMap[keys[i]];
        qDebug() << "Childs" << parent->id << keys[i] << taskParentMap[keys[i]].count() << "|";
        QList<ITaskListModel::TaskInfo*> childTaskList = taskParentMap[keys[i]].values();
        for(int j = 0; j < childTaskList.count(); j++)
        {
           childTaskList[j]->parent = parent;
           qDebug() << "P" << childTaskList[j]->id << parent->id;
        }
        parent->childTasks = childTaskList;
    }

    for(int i = 0; i < rootTask->childTasks.count(); i++)
        qDebug() << rootTask->childTasks[i]->name;

    return rootTask;
}

bool TaskListModel::Open(IPluginModel *parent, QWidget *parentWidget, int id)
{
    qDebug() << "TaskListModel runs";
    qDebug() << "EmptyModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }
    myModelId = id;
    myParent = parent;
    myParentWidget = parentWidget;
    activeViewId = 0;

    if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget)){
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

bool TaskListModel::Close()
{
    if(activeViewId != -1)
    {
        if(!viewPlugins[activeViewId].plugin->Close())
        {
            qDebug() << "My view can't close!";
            return false;
        }
        else
        {
            ITaskListModel::TaskInfo info;
            DeleteTask(rootTask);
            activeViewId = -1;
            myParent->ChildSelfClosed(myModelId);
            return true;
        }
    }
    else
        return true;
}

void TaskListModel::ChildSelfClosed(int id)
{

}

void TaskListModel::AddView(IPluginView *plugin, MetaInfo *meta)
{
    PluginInfo<IPluginView> newPlugin = {plugin, meta};
    viewPlugins.append(newPlugin);
    newPlugin.plugin->SetModel(qobject_cast<QObject*>(this));
    qDebug() << "IPluginView succesfully set.";
}

bool TaskListModel::AddTask(TaskInfo *taskParent, TaskInfo taskData)
{
    qDebug() << "Add task";
    TaskInfo *newTask = new TaskInfo();
    newTask->name = taskData.name;
    qDebug() << taskParent->childTasks;
    if(taskParent != NULL)
        taskParent->childTasks.append(newTask);
    newTask->parent = taskParent;

    ITaskDataManagerPlugin::TaskInfo managerTask = ConvertToManagerTaskInfo(*newTask);
    qDebug() << managerTask.id << managerTask.name << managerTask.parent << managerTask.position;
    newTask->id = dataManager->AddTask(tableName, managerTask);
}

bool TaskListModel::EditTask(ITaskListModel::TaskInfo *task, ITaskListModel::TaskInfo taskData)
{
    task->id = taskData.id;
    task->name = taskData.name;

    ITaskDataManagerPlugin::TaskInfo managerTask = ConvertToManagerTaskInfo(*task);
    dataManager->EditTask(tableName, managerTask);
}

bool TaskListModel::DeleteTask(ITaskListModel::TaskInfo *task)
{
    if(!task)
        return false;
    if(task->parent)
        task->parent->childTasks.removeOne(task);
    DeleteTaskRecursive(task);

    dataManager->DeleteTask(tableName, task->id);
}

ITaskDataManagerPlugin::TaskInfo TaskListModel::ConvertToManagerTaskInfo(ITaskListModel::TaskInfo &task)
{
    ITaskDataManagerPlugin::TaskInfo managerTask;
    qDebug() << task.id << task.name << task.parent;
    //Set id
    managerTask.id = task.id;
    // Set name
    managerTask.name = task.name;
//    // Set level
//    managerTask.level = 0;
//    ITaskListModel::TaskInfo* pTask = task.parent;
//    while(pTask)
//    {
//        ++managerTask.level;
//        pTask = pTask->parent;
//    }
    // Set parent
    managerTask.parent = task.parent ? task.parent->id : -1;
    // Set position
    if(task.parent)
    {
        managerTask.position = -1;
        for(int i = 0; i < task.parent->childTasks.count(); i++)
            if(task.parent->childTasks[i]->id == task.id)
                managerTask.position = i;
        // If not exist - add to end
        if(managerTask.position == -1)
            managerTask.position = task.parent->childTasks.count();
    }
    else
    {
        managerTask.position = 0;
    }
    return managerTask;
}

void TaskListModel::DeleteTaskRecursive(ITaskListModel::TaskInfo *task)
{
    if(task->childTasks.count() != 0)
    {
        for(int i = 0; i < task->childTasks.count(); i++)
        {
            DeleteTaskRecursive(task->childTasks[i]);
        }
    }
    dataManager->DeleteTask(tableName, task->id);
    delete task;
}
