#include "dayplan.h"

DayPlan::DayPlan() :
    PluginBase()
{
    taskTreeModel = nullptr;
    taskDataModel = nullptr;
    dateDataModel = nullptr;
    dataManager = nullptr;
    tableName = "IUserTaskManager";
    relationName = "IDayPlan";
}

DayPlan::~DayPlan()
{
}

void DayPlan::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IUserTaskManager", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            taskTreeModel = qobject_cast<IUserTaskManager*>(instance);
        }
        else if(!QString::compare(interfaceName, "IExtendableDataManager", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            dataManager = qobject_cast<IExtendableDataManager*>(instance);
        }
    }
    PluginBase::onAllReferencesSet();
}

void DayPlan::onAllReferencesReady()
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

bool DayPlan::open()
{
    dataManager->SetActiveExtention(tableName, relationName);
    return PluginBase::open();
}

QAbstractItemModel *DayPlan::GetTaskModel()
{
    return taskDataModel;
}

QAbstractItemModel *DayPlan::GetDateModel()
{
    return dateDataModel;
}

void DayPlan::SetDataTypeEditor(QWidget *widget)
{
    dataManager->RegisterExtentionFieldEditor(relationName, "datetime", widget);
}
