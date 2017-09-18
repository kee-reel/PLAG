#include "extendabledamanager.h"

ExtendableDataBaseManagerPlugin::ExtendableDataBaseManagerPlugin()
{
    dataSource = NULL;
}

ExtendableDataBaseManagerPlugin::~ExtendableDataBaseManagerPlugin()
{
    QHash<QString, TableHandler*>::Iterator tablesIter = tableHandlers.begin();
    while(tablesIter != tableHandlers.end())
    {
        delete tablesIter.value();
        ++tablesIter;
    }
}

void ExtendableDataBaseManagerPlugin::OnAllSetup()
{

}

QString ExtendableDataBaseManagerPlugin::GetLastError()
{
    return lastError;
}

void ExtendableDataBaseManagerPlugin::SetPluginInfo(PluginInfo *pluginInfo)
{

}

void ExtendableDataBaseManagerPlugin::AddReferencePlugin(PluginInfo *pluginInfo)
{
    dataSource = qobject_cast<IDataBaseSourcePlugin*>(pluginInfo->Instance);
    if(!dataSource)
    {
        qDebug() << pluginInfo->Meta->Name << "is not ExtendableDataBaseManagerPlugin.";
    }
    qDebug() << "ExtendableDataBaseManagerPlugin succesfully set.";
}

void ExtendableDataBaseManagerPlugin::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

void ExtendableDataBaseManagerPlugin::SetupTable(QString &tableName)
{
    tableName = tableName.toLower();
    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, this, tableName);
}

QList<ExtendableDataBaseManagerPlugin::ManagerDataItem> ExtendableDataBaseManagerPlugin::GetDataList(QString tableName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetData();
}

IExtendableDataManager::ManagerDataItem ExtendableDataBaseManagerPlugin::GetDataItem(QString tableName, int id)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetItem(id);
}

QAbstractItemModel *ExtendableDataBaseManagerPlugin::GetDataModel(QString tableName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetModel();
}

QMap<QString, QVariant::Type> ExtendableDataBaseManagerPlugin::GetTableHeader(QString tableName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetHeader();
}

bool ExtendableDataBaseManagerPlugin::SetRelation(QString tableName, QString relationName, QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->SetRelation(relationName, fields, defaultData);
}

bool ExtendableDataBaseManagerPlugin::DeleteRelation(QString tableName, QString relationName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->DeleteRelation(relationName);
}

bool ExtendableDataBaseManagerPlugin::SetActiveRelation(QString tableName, QString relationName)
{
    SetupTable(tableName);
    tableHandlers[tableName]->SetActiveRelation(relationName);
    return true;
}

int ExtendableDataBaseManagerPlugin::AddItem(QString tableName, ManagerDataItem item)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->AddItem(item);
}

bool ExtendableDataBaseManagerPlugin::UpdateItem(QString tableName, ManagerDataItem item)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->UpdateItem(item);
}

bool ExtendableDataBaseManagerPlugin::DeleteItem(QString tableName, int id)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->DeleteItem(id);
}
