#include "dayplanmodel.h"

DayPlanModel::DayPlanModel() :
    PluginBase()
{
    taskTreeModel = nullptr;
    taskDataModel = nullptr;
    dateDataModel = nullptr;
    dataManager = nullptr;
    tableName = "ITaskTreeModel";
    relationName = "IDayPlanModel";
}

DayPlanModel::~DayPlanModel()
{
}

void DayPlanModel::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "ITaskTreeModel", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            taskTreeModel = qobject_cast<ITaskTreeModel*>(instance);
        }
        else if(!QString::compare(interfaceName, "IExtendableDataManager", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            dataManager = qobject_cast<IExtendableDataManager*>(instance);
        }
    }
    PluginBase::onAllReferencesSet();
}

void DayPlanModel::onAllReferencesReady()
{
    QMap<QString, QVariant::Type> newRelationStruct = {
        {"Date",        QVariant::String},
    };
    QVector<QVariant> defaultData;
    defaultData << QDateTime::currentDateTime().toString(Qt::ISODate);
    dataManager->AddExtention(tableName, relationName, newRelationStruct, defaultData);
    dataManager->AddExtention(relationName, relationName, newRelationStruct, defaultData);

    taskDataModel = dataManager->GetDataModel(tableName);
    dateDataModel = dataManager->GetDataModel(relationName);

    PluginBase::onAllReferencesReady();
}

bool DayPlanModel::open()
{
    dataManager->SetActiveExtention(tableName, relationName);
    return PluginBase::open();
}

QAbstractItemModel *DayPlanModel::GetTaskModel()
{
    return taskDataModel;
}

QAbstractItemModel *DayPlanModel::GetDateModel()
{
    return dateDataModel;
}

void DayPlanModel::SetDataTypeEditor(QWidget *widget)
{
    dataManager->RegisterExtentionFieldEditor(relationName, "datetime", widget);
}
