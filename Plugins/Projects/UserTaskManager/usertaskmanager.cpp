#include "usertaskmanager.h"

UserTaskManager::UserTaskManager()
{
    tableName = "iUserTaskManager";
    relationName = "iUserTaskManager";
    dataManager = nullptr;
    treeModel = nullptr;
}

UserTaskManager::~UserTaskManager()
{
}

void UserTaskManager::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IExtendableDataManager", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            dataManager = qobject_cast<IExtendableDataManager*>(instance);
        }
    }
    PluginBase::onAllReferencesSet();
}

QAbstractItemModel* UserTaskManager::GetTreeModel()
{
    return treeModel;
}

void UserTaskManager::onAllReferencesReady()
{
    QMap<QString, QVariant::Type> newRelationStruct =
    {
        {"name",        QVariant::String},
    };
    QVector<QVariant> defaultData;
    defaultData << "New task";
    dataManager->AddExtention(tableName, relationName, newRelationStruct, defaultData);

    treeModel = dataManager->GetDataModel(tableName);

    PluginBase::onAllReferencesReady();
}


bool UserTaskManager::open()
{
    dataManager->SetActiveExtention(tableName, relationName);
    PluginBase::open();
}
