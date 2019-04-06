#include "tasktreemodel.h"

TaskTreeModel::TaskTreeModel()
{
    tableName = "itasktreemodel";
    relationName = "itasktreemodel";
    dataManager = nullptr;
    treeModel = nullptr;
}

TaskTreeModel::~TaskTreeModel()
{
}

void TaskTreeModel::onAllReferencesSet()
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

QAbstractItemModel* TaskTreeModel::GetTreeModel()
{
    return treeModel;
}

void TaskTreeModel::onAllReferencesReady()
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


bool TaskTreeModel::open()
{
    dataManager->SetActiveExtention(tableName, relationName);
    PluginBase::open();
}
