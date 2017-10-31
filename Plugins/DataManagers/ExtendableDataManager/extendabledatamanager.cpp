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
    dataSource->Setup();
}

void ExtendableDataBaseManagerPlugin::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

bool ExtendableDataBaseManagerPlugin::RegisterExtentionFieldEditor(QString relation, QString field, QWidget *widget)
{
    QVariant value = widget->property("value");

    if(widget == NULL || !value.isValid())
        return false;

    relation = relation.toLower();
    field = field.toLower();
    dataTypeEditorsMap[relation].insert(field, widget);

    foreach (auto table, tableHandlers)
    {
        if(table->HasRelation(relation))
            table->SetDataTypeEditor(relation, field, widget);
    }
}

QWidget *ExtendableDataBaseManagerPlugin::GetExtentionFieldEditor(QString relation, QString field)
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

QAbstractItemModel *ExtendableDataBaseManagerPlugin::GetDataModel(QVector<QPair<QString, QString> > dataModelFields)
{
    auto iter = dataModelFields.begin();

    while(iter != dataModelFields.end())
    {
        auto tableName = iter->first;

        if(!tableHandlers.contains(tableName))
        {
            SetupTable(tableName);
            SetupDataTypeEditors(tableName);
        }

        ++iter;
    }

    return CreateProxy(dataModelFields);
}

QAbstractItemModel * ExtendableDataBaseManagerPlugin::CreateProxy(QVector<QPair<QString, QString> > &dataModelFields)
{
    auto iter = dataModelFields.begin();

    while(iter != dataModelFields.end())
    {
        auto tableName = iter->first;

        if(!tableHandlers.contains(tableName))
        {
            SetupTable(tableName);
            SetupDataTypeEditors(tableName);
        }

        ++iter;
    }

    //    QAbstractItemModel *itemModel = tableHandlers[tableName]->GetModel();
}

QMap<QString, QVariant::Type> ExtendableDataBaseManagerPlugin::GetTableHeader(QString tableName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetHeader();
}

bool ExtendableDataBaseManagerPlugin::AddExtention(QString tableName, QString extentionName,
        QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->SetRelation(extentionName, fields, defaultData);
}

bool ExtendableDataBaseManagerPlugin::DeleteExtention(QString tableName, QString extentionName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->DeleteRelation(extentionName);
}

bool ExtendableDataBaseManagerPlugin::SetActiveExtention(QString tableName, QString extentionName)
{
    SetupTable(tableName);
    tableHandlers[tableName]->SetActiveRelation(extentionName);
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
