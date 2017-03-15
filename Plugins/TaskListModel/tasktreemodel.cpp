#include "tasktreemodel.h"

TaskTreeModel::TaskTreeModel()
{
    tableName = "TaskTree";
    activeViewId = -1;
    dataManager = NULL;
    treeModel = NULL;
}

TaskTreeModel::~TaskTreeModel()
{
}

void TaskTreeModel::OnAllSetup()
{

}

QString TaskTreeModel::GetLastError()
{

}

void TaskTreeModel::AddChildModel(IModelPlugin *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IModelPlugin> newPlugin = {plugin, meta};
    childModelPlugins.append(newPlugin);
}

void TaskTreeModel::AddView(IViewPlugin *view, MetaInfo *meta)
{
    PluginInfo<IViewPlugin> newPlugin = {view, meta};
    viewPlugins.append(newPlugin);
    qDebug() << "IPluginView succesfully set.";
}

void TaskTreeModel::AddDataManager(QObject *DBTool)
{
    qDebug() <<  "is not IExtendableDataBaseManagerPlugin.";
    this->dataManager = qobject_cast<IExtendableDataBaseManagerPlugin*>(DBTool);
    if(!this->dataManager)
    {
        qDebug() << DBTool->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
    if(!treeModel)
        treeModel = new TaskTreeItemModel(tableName, dataManager);
}

bool TaskTreeModel::Open(IModelPlugin *parent, QWidget *parentWidget, int id)
{
    qDebug() << "TaskListModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }
    myModelId = id;
    myParent = parent;
    myParentWidget = parentWidget;
    activeViewId = 0;

    qDebug() << viewPlugins[activeViewId].meta->Name;
    if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget))
    {
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

bool TaskTreeModel::Close()
{
    myParent->ChildSelfClosed(myModelId);
    activeViewId = -1;
    return true;
}

void TaskTreeModel::ChildSelfClosed(int id)
{

}

QAbstractItemModel* TaskTreeModel::GetTreeModel()
{
    return treeModel;
}
