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

void TaskTreeModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void TaskTreeModel::OnAllSetup()
{

}

QString TaskTreeModel::GetLastError()
{
    return "";
}

void TaskTreeModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
        case PLUGINVIEW:{
            viewPlugins.append(pluginInfo);
            connect(pluginInfo->Instance, SIGNAL(OnClose(PluginInfo*)), SLOT(ReferencePluginClosed(PluginInfo*)));
        }break;

        case DATAMANAGER:{
            this->dataManager = qobject_cast<IExtendableDataBaseManagerPlugin*>(pluginInfo->Instance);
            if(!this->dataManager){
                qDebug() << pluginInfo->Meta->Name << "is not IExtendableDataBaseManagerPlugin.";
                return;
            }
            QMap<QString, QVariant::Type> newRelationStruct = {
                {"name",        QVariant::String},
            };
            QVector<QVariant> defaultData;
            dataManager->SetRelation(tableName, relationName, newRelationStruct, defaultData);
        }break;

        case ROOTMODEL:{
            myParent = qobject_cast<IModelPlugin*>(pluginInfo->Instance);
            if(!myParent){
                qDebug() << pluginInfo->Meta->Name << "is not MainMenu.";
                return;
            }
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            myParent->AddReferencePlugin(this->pluginInfo);
        }break;
    }
}

void TaskTreeModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
    if(pluginInfo->Meta->Type == PLUGINVIEW)
    {
        Close();
    }
}

//void TaskTreeModel::AddView(QObject *instance, MetaInfo *meta)
//{
//    IViewPlugin *view = qobject_cast<IViewPlugin*>(instance);
//    //PluginInfo<IViewPlugin> newPlugin = {view, meta};
//    //viewPlugins.append(newPlugin);
//    qDebug() << "IPluginView succesfully set.";
//    connect(instance, SIGNAL(OnClose(IViewPlugin*)), SLOT(RelatedViewClosed(IViewPlugin*)));
//}

//void TaskTreeModel::AddDataManager(QObject *DBTool)
//{
//    qDebug() <<  "is not IExtendableDataBaseManagerPlugin.";
//    this->dataManager = qobject_cast<IExtendableDataBaseManagerPlugin*>(DBTool);
//    if(!this->dataManager)
//    {
//        qDebug() << DBTool->objectName() << "is not IExtendableDataBaseManagerPlugin.";
//        return;
//    }
//    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";

//    QMap<QString, QVariant::Type> newRelationStruct = {
//        {"name",        QVariant::String},
//    };
//    QVector<QVariant> defaultData;
//    defaultData << "New task";
//    dataManager->SetRelation(tableName, relationName, newRelationStruct, defaultData);
//}

//void TaskTreeModel::AddModel(QObject *instance, MetaInfo *meta)
//{
//    qDebug() <<  "is not MainMenu.";
//    myParent = qobject_cast<IModelPlugin*>(instance);
//    if(!this->dataManager)
//    {
//        qDebug() << instance->objectName() << "is not MainMenu.";
//        return;
//    }
//    qDebug() << "MainMenu succesfully set.";
//    connect(this, SIGNAL(OnClose(IModelPlugin*)), instance, SLOT(RelatedModelClosed(IModelPlugin*)));
//}

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
    if(!activeView) activeView = viewPlugins.first()->Plugin.view;
    if(!activeView->Open(this, myParentWidget))
    {
        qDebug() << "Can't open first view!";
        return false;
    }
    return true;
}

//void TaskTreeModel::RelatedModelClosed(IModelPlugin *model)
//{

//}

//void TaskTreeModel::RelatedViewClosed(IViewPlugin *view)
//{
//    Close();
//}

void TaskTreeModel::Close()
{
    emit OnClose(pluginInfo);
    emit OnClose();
}

QString TaskTreeModel::GetDataName()
{
    return tableName;
}

QAbstractItemModel* TaskTreeModel::GetTreeModel()
{
    if(!treeModel) treeModel = dataManager->GetDataModel(tableName);
    return treeModel;
}

void TaskTreeModel::SetRelationDelegate(QString relation, ITaskRelationDelegate *delegate)
{
    taskRelationDelegates.insert(relation, delegate);
}

QMap<QString, ITaskTreeModel::ITaskRelationDelegate*> TaskTreeModel::GetRelationDelegates()
{
    return taskRelationDelegates;
}

void TaskTreeModel::SetupModel()
{
    if(dataManager == NULL)
        return;
    treeModel = dataManager->GetDataModel(tableName);
    dataManager->SetActiveRelation(tableName, relationName);
}
