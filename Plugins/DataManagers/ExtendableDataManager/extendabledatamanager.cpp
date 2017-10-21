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
        qDebug() << pluginInfo->Meta->Name << "is not IDataBaseSourcePlugin.";
    }
    qDebug() << "IDataBaseSourcePlugin succesfully set.";
    dataSource->SetPassword("rqCZB63Fr7tmTB");
    dataSource->UpdatePortsList();
}

void ExtendableDataBaseManagerPlugin::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool ExtendableDataBaseManagerPlugin::RegisterDataTypeEditor(QString relation, QString field, QWidget *widget)
{
    QVariant value = widget->property("value");
    if(widget == NULL || !value.isValid())
        return false;

    relation = relation.toLower();
    field = field.toLower();
    dataTypeEditorsMap[relation].insert(field, widget);

    foreach (auto table, tableHandlers) {
        if(table->HasRelation(relation))
            table->SetDataTypeEditor(relation, field, widget);
    }
}

QWidget *ExtendableDataBaseManagerPlugin::GetDataTypeEditor(QString relation, QString field)
{
    if(dataTypeEditorsMap.contains(relation) && dataTypeEditorsMap[relation].contains(field))
        return dataTypeEditorsMap[relation].value(field);
    return NULL;
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

void ExtendableDataBaseManagerPlugin::SetupDataTypeEditors(QString tableName)
{
    auto relationIter = dataTypeEditorsMap.begin();
    while(relationIter != dataTypeEditorsMap.end())
    {
        auto tablesIter = tableHandlers.begin();
        while(tablesIter != tableHandlers.end())
        {
            if(tablesIter.value()->HasRelation(relationIter.key()))
            {
                auto fieldIter = relationIter.value().begin();
                while(fieldIter != relationIter.value().end())
                {
                    tableHandlers[tableName]->SetDataTypeEditor(relationIter.key(), fieldIter.key(), fieldIter.value());
                    ++fieldIter;
                }
            }
            ++tablesIter;
        }
        ++relationIter;
    }
}

QAbstractItemModel *ExtendableDataBaseManagerPlugin::GetDataModel(QString tableName)
{
    SetupTable(tableName);
    QAbstractItemModel *itemModel = tableHandlers[tableName]->GetModel();
    SetupDataTypeEditors(tableName);
    return itemModel;
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
