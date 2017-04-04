#include "tasktreemodel.h"

TaskTreeModel::TaskTreeModel()
{
    tableName = "TaskTree";
    activeView = NULL;
    activeModel = NULL;
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

bool TaskTreeModel::Open(IModelPlugin *parent, QWidget *parentWidget)
{
    qDebug() << "TaskListModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }
    myParent = parent;
    myParentWidget = parentWidget;

    if(treeModel)
        treeModel->LoadData();
    if(!activeView)
        activeView = viewPlugins.first().plugin;
    if(!activeView->Open(myParentWidget))
    {
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

bool TaskTreeModel::CloseFromView(IViewPlugin *view)
{
    myParent->ChildSelfClosed(this);
    activeView = NULL;
    return true;
}

void TaskTreeModel::ChildSelfClosed(IModelPlugin *child)
{

}

QString TaskTreeModel::GetDataName()
{
    return tableName;
}

QAbstractItemModel* TaskTreeModel::GetTreeModel()
{
    return treeModel;
}
