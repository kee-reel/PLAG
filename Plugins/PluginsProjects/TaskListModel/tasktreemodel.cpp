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

void TaskTreeModel::onAllReferencesSetStateChanged()
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

}

QAbstractItemModel* TaskTreeModel::GetTreeModel()
{
    if(!treeModel)
    {
        SetupModel();
    }
    return treeModel;
}

void TaskTreeModel::SetupModel()
{
    QMap<QString, QVariant::Type> newRelationStruct =
    {
        {"name",        QVariant::String},
    };
    QVector<QVariant> defaultData;
    defaultData << "New task";
    dataManager->AddExtention(tableName, relationName, newRelationStruct, defaultData);
    dataManager->SetActiveExtention(tableName, relationName);

    treeModel = dataManager->GetDataModel(tableName);
}
