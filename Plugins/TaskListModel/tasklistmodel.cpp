#include "tasklistmodel.h"

TaskListModel::TaskListModel()
{
    activeView = NULL;

    rootTask = NULL;
}

TaskListModel::~TaskListModel()
{
}

void TaskListModel::AddChildPlugin(IPluginModel *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    childPlugins.insert(plugin, meta);
}

void TaskListModel::SetDataManager(QObject *DBTool)
{
    this->DBTool = qobject_cast<ITaskDataManagerPlugin*>(DBTool);
    if(!this->DBTool)
    {
        qDebug() << DBTool->objectName() << "is not ITaskDBToolPlugin.";
        return;
    }
    qDebug() << "ITaskDBToolPlugin succesfully set.";
}

QString TaskListModel::GetError()
{

}

bool TaskListModel::Open(QWidget *parent)
{
    qDebug() << "TaskListModel runs";
    this->parent = parent;
    if(viewPlugins.count() == 0)
    {
        qDebug() << "I dont have any views!";
        return false;
    }
    if(activeView != NULL)
    {
        bool isClosed = activeView->Close();
        if(!isClosed) return false;
    }
    activeView = viewPlugins.begin().key();
    if(!activeView)
    {
        qDebug() << "Active view is null!";
        return false;
    }
    DBTool->GetTaskTree("MyTestTree");
    return activeView->Open(this->parent);
}

bool TaskListModel::Close()
{
    if(activeView != NULL)
        return activeView->Close();
    else
        return true;
}

void TaskListModel::AddView(IPluginView *plugin, MetaInfo *meta)
{
    IPluginView* view = plugin;
    viewPlugins.insert(view, meta);
    view->SetModel(qobject_cast<QObject*>(this));
    qDebug() << "IPluginView succesfully set.";
}

ITaskListModel::TaskInfo *TaskListModel::GetRootTask()
{
//    if(!rootTask)
//    {
//        DBTool->
//    }

    return NULL;
}

void TaskListModel::SetRootTask(ITaskListModel::TaskInfo *rootTask)
{
    if(this->rootTask != rootTask)
    {
        delete this->rootTask;
    }
    this->rootTask = rootTask;
}
