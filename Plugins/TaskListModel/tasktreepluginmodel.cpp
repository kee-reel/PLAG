#include "tasktreepluginmodel.h"

TaskTreePluginModel::TaskTreePluginModel()
{
    tableName = "TaskTree";
    activeViewId = -1;
    dataManager = NULL;
}

TaskTreePluginModel::~TaskTreePluginModel()
{
}

void TaskTreePluginModel::AddChildModel(IPluginModel *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IPluginModel> newPlugin = {plugin, meta};
    childModelPlugins.append(newPlugin);
}

void TaskTreePluginModel::AddDataManager(QObject *DBTool)
{
    this->dataManager = qobject_cast<ITreeDataManagerPlugin*>(DBTool);
    if(!this->dataManager)
    {
        qDebug() << DBTool->objectName() << "is not ITaskDBToolPlugin.";
        return;
    }
    qDebug() << "ITaskDBToolPlugin succesfully set.";
}

QString TaskTreePluginModel::GetError()
{

}

QAbstractItemModel* TaskTreePluginModel::GetTreeModel()
{
    if(!dataManager)
    {
        qDebug() << "Data manager not set!";
        return NULL;
    }
    QList<ITreeDataManagerPlugin::TaskInfo> managerTaskList = dataManager->GetTaskTree(tableName);
    treeModel = new TaskTreeItemModel(tableName, dataManager, managerTaskList);
    return treeModel;
}

bool TaskTreePluginModel::Open(IPluginModel *parent, QWidget *parentWidget, int id)
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

bool TaskTreePluginModel::Close()
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
            activeViewId = -1;
            myParent->ChildSelfClosed(myModelId);
            return true;
        }
    }
    else
        return true;
}

void TaskTreePluginModel::ChildSelfClosed(int id)
{

}

void TaskTreePluginModel::AddView(IPluginView *plugin, MetaInfo *meta)
{
    PluginInfo<IPluginView> newPlugin = {plugin, meta};
    viewPlugins.append(newPlugin);
    newPlugin.plugin->SetModel(qobject_cast<QObject*>(this));
    qDebug() << "IPluginView succesfully set.";
}
