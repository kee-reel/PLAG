#include "taskcalendar.h"

TaskCalendar::TaskCalendar() :
    PluginBase(nullptr)
{
}

TaskCalendar::~TaskCalendar()
{
}

void TaskCalendar::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IExtendableDataManager", Qt::CaseInsensitive))
        {
            dataManager = castPluginToInterface<IExtendableDataManager>(plugin);
        }
        else if(!QString::compare(interfaceName, "ITaskTreeModel", Qt::CaseInsensitive))
        {
            taskTree = castPluginToInterface<ITaskTreeModel>(plugin);
        }
    }
    PluginBase::onAllReferencesSet();
}

void TaskCalendar::onAllReferencesReady()
{
    QMap<QString, QVariant::Type> newRelationStruct = {
        {"Date",   QVariant::DateTime}
    };
    QVector<QVariant> defaultData;
    defaultData << QDateTime::currentDateTime().toString(Qt::ISODate);
    dataManager->AddExtention("ITaskTreeModel", "ITaskCalendar", newRelationStruct, defaultData);

    dataManager->SetActiveExtention("ITaskTreeModel", "ITaskCalendar");

    PluginBase::onAllReferencesReady();
}

void TaskCalendar::LinkEditorWidget(QWidget *widget)
{
}
