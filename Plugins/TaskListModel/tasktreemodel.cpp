#include "tasktreemodel.h"

TaskTreeModel::TaskTreeModel()
{
    tableName = "tasktree";
    relationName = "task";
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

    QMap<QString, QVariant::Type> newRelationStruct = {
        {"name",        QVariant::String},
    };
    QVector<QVariant> defaultData;
    defaultData << "New task";
    dataManager->SetRelation(tableName, relationName, newRelationStruct, defaultData);
}

void TaskTreeModel::AddParentModel(QObject *model, MetaInfo *meta)
{
    qDebug() <<  "is not MainMenu.";
    myParent = qobject_cast<IModelPlugin*>(model);
    if(!this->dataManager)
    {
        qDebug() << model->objectName() << "is not MainMenu.";
        return;
    }
    qDebug() << "MainMenu succesfully set.";
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

    SetupModel();
    if(!activeView) activeView = viewPlugins.first().plugin;
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
    myParent->ChildSelfClosed(this);
}

QString TaskTreeModel::GetDataName()
{
    return tableName;
}

QAbstractItemModel* TaskTreeModel::GetTreeModel()
{
    if(treeModel) treeModel = dataManager->GetDataModel(tableName);
    return treeModel;
}

void TaskTreeModel::SetupModel()
{
    treeModel = dataManager->GetDataModel(tableName);
    dataManager->SetActiveRelation(tableName, relationName);
}
