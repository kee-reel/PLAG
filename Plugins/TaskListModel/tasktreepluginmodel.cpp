#include "tasktreepluginmodel.h"

TaskTreePluginModel::TaskTreePluginModel()
{
    tableName = "TaskTree";
    activeViewId = -1;
    dataManager = NULL;
    treeModel = NULL;
}

TaskTreePluginModel::~TaskTreePluginModel()
{
}

void TaskTreePluginModel::OnAllSetup()
{

}

QString TaskTreePluginModel::GetLastError()
{

}

void TaskTreePluginModel::AddChildModel(IModelPlugin *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IModelPlugin> newPlugin = {plugin, meta};
    childModelPlugins.append(newPlugin);
}

void TaskTreePluginModel::AddDataManager(QObject *DBTool)
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

QString TaskTreePluginModel::GetError()
{

}

QAbstractItemModel* TaskTreePluginModel::GetTreeModel()
{
    return treeModel;
}

bool TaskTreePluginModel::Open(IModelPlugin *parent, QWidget *parentWidget, int id)
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
    qDebug() << viewPlugins[activeViewId].plugin->Close();
    if(!viewPlugins[activeViewId].plugin->Open(activeViewId, myParentWidget))
    {
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

void TaskTreePluginModel::AddView(IViewPlugin *plugin, MetaInfo *meta)
{
    PluginInfo<IViewPlugin> newPlugin = {plugin, meta};
    viewPlugins.append(newPlugin);
    qDebug() << "IPluginView succesfully set.";
}
