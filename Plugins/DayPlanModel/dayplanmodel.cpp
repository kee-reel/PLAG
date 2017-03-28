#include "dayplanmodel.h"

TaskSketchModel::TaskSketchModel()
{
    tableName = "TaskTree";
    activeViewId = -1;
    dataManager = NULL;
}

TaskSketchModel::~TaskSketchModel()
{
}

void TaskSketchModel::OnAllSetup()
{

}

QString TaskSketchModel::GetLastError()
{

}

void TaskSketchModel::AddChildModel(IModelPlugin *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IModelPlugin> newPlugin = {plugin, meta};
    childModelPlugins.append(newPlugin);
}

void TaskSketchModel::AddView(IViewPlugin *view, MetaInfo *meta)
{
    PluginInfo<IViewPlugin> newPlugin = {view, meta};
    viewPlugins.append(newPlugin);
    qDebug() << "IPluginView succesfully set.";
}

void TaskSketchModel::AddDataManager(QObject *DBTool)
{
    qDebug() <<  "is not IExtendableDataBaseManagerPlugin.";
    this->dataManager = qobject_cast<IExtendableDataBaseManagerPlugin*>(DBTool);
    if(!this->dataManager)
    {
        qDebug() << DBTool->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";\
}

bool TaskSketchModel::Open(IModelPlugin *parent, QWidget *parentWidget)
{
    qDebug() << "TaskListModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }
    myParent = parent;
    myParentWidget = parentWidget;
    activeViewId = 0;

    qDebug() << viewPlugins[activeViewId].meta->Name;
    if(!viewPlugins[activeViewId].plugin->Open(myParentWidget))
    {
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

bool TaskSketchModel::CloseFromView(IViewPlugin *view)
{
    myParent->ChildSelfClosed(this);
    activeViewId = -1;
    return true;
}

void TaskSketchModel::ChildSelfClosed(IModelPlugin *child)
{

}
