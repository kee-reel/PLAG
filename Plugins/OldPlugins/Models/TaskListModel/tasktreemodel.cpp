#include "tasktreemodel.h"

TaskTreeModel::TaskTreeModel()
{
    tableName = "itasktreemodel";
    relationName = "itasktreemodel";
    activeView = nullptr;
    activeModel = nullptr;
    dataManager = nullptr;
    treeModel = nullptr;
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
    if(!dataManager)
        return;

    QMap<QString, QVariant::Type> newRelationStruct =
    {
        {"name",        QVariant::String},
    };
    QVector<QVariant> defaultData;
    defaultData << "New task";
    dataManager->AddExtention(tableName, relationName, newRelationStruct, defaultData);
}

QString TaskTreeModel::GetLastError()
{
    return "";
}

void TaskTreeModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
        case VIEWPLUGIN:
            {
                viewPlugins.append(pluginInfo);
                connect(pluginInfo->Instance, SIGNAL(OnClose(PluginInfo*)), SLOT(ReferencePluginClosed(PluginInfo*)));
            } break;

        case DATAMANAGERPLUGIN:
            {
                this->dataManager = qobject_cast<IExtendableDataManager*>(pluginInfo->Instance);

                if(!this->dataManager)
                {
                    qDebug() << pluginInfo->Meta->Name << "is not IExtendableDataManager.";
                    return;
                }
            } break;

        case COREPLUGIN:
            {
                myParent = pluginInfo->Plugin.model;

                if(!myParent)
                {
                    qDebug() << pluginInfo->Meta->Name << "is not MainMenu.";
                    return;
                }

                myParent->AddReferencePlugin(this->pluginInfo);
            } break;
    }
}

void TaskTreeModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
    if(pluginInfo->Meta->Type == VIEWPLUGIN)
    {
        Close();
    }
}

bool TaskTreeModel::Open(IModelPlugin *parent)
{
    qDebug() << "TaskListModel runs";

    if(viewPlugins.count() == 0)
    {
        qDebug() << "I dont have any views!";
        return false;
    }

    myParent = parent;
    SetupModel();

    if(!activeView)
        activeView = viewPlugins.first()->Plugin.view;

    if(!activeView->Open(this))
    {
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

void TaskTreeModel::Close()
{
    emit OnClose(pluginInfo);
    emit OnClose();
}

QAbstractItemModel* TaskTreeModel::GetTreeModel()
{
    if(!dataManager)
        return nullptr;

    if(!treeModel)
        treeModel = dataManager->GetDataModel(tableName);

    return treeModel;
}

void TaskTreeModel::SetupModel()
{
    if(!dataManager)
        return;

    treeModel = dataManager->GetDataModel(tableName);
    dataManager->SetActiveExtention(tableName, relationName);
}
