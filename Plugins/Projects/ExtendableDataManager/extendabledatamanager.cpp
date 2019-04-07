#include "extendabledamanager.h"

ExtendableDataBaseManager::ExtendableDataBaseManager() :
    PluginBase ()
{
    dataSource = nullptr;
}

ExtendableDataBaseManager::~ExtendableDataBaseManager()
{
    QHash<QString, TableHandler*>::Iterator tablesIter = tableHandlers.begin();

    while(tablesIter != tableHandlers.end())
    {
        delete tablesIter.value();
        ++tablesIter;
    }
}

void ExtendableDataBaseManager::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IDataBase", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            dataSource = qobject_cast<IDataBase*>(instance);
            dataSource->SetPassword("rqCZB63Fr7tmTB");
        }
    }
    PluginBase::onAllReferencesSet();
}

bool ExtendableDataBaseManager::RegisterExtentionFieldEditor(QString relation, QString field, QWidget *widget)
{
    QVariant value = widget->property("value");

    if(widget == nullptr || !value.isValid())
        return false;

    relation = relation.toLower();
    field = field.toLower();
    dataTypeEditorsMap[relation].insert(field, widget);

    foreach (auto table, tableHandlers)
    {
        if(table->HasRelation(relation))
            table->SetDataTypeEditor(relation, field, widget);
    }
    return true;
}

QWidget *ExtendableDataBaseManager::GetExtentionFieldEditor(QString relation, QString field)
{
    if(dataTypeEditorsMap.contains(relation) && dataTypeEditorsMap[relation].contains(field))
        return dataTypeEditorsMap[relation].value(field);

    return nullptr;
}

void ExtendableDataBaseManager::SetupTable(QString &tableName)
{
    tableName = tableName.toLower();

    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, this, tableName);
}

QList<ExtendableDataBaseManager::ManagerDataItem> ExtendableDataBaseManager::GetDataList(QString tableName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetData();
}

IExtendableDataManager::ManagerDataItem ExtendableDataBaseManager::GetDataItem(QString tableName, int id)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetItem(id);
}

void ExtendableDataBaseManager::SetupDataTypeEditors(QString tableName)
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

QAbstractItemModel *ExtendableDataBaseManager::GetDataModel(QString tableName)
{
    SetupTable(tableName);
    QAbstractItemModel *itemModel = tableHandlers[tableName]->GetModel();
    SetupDataTypeEditors(tableName);
    return itemModel;
}

QAbstractItemModel *ExtendableDataBaseManager::GetDataModel(QVector<QPair<QString, QString> > dataModelFields)
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

QAbstractItemModel * ExtendableDataBaseManager::CreateProxy(QVector<QPair<QString, QString> > &dataModelFields)
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

QMap<QString, QVariant::Type> ExtendableDataBaseManager::GetTableHeader(QString tableName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetHeader();
}

bool ExtendableDataBaseManager::AddExtention(QString tableName, QString extentionName,
        QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->SetRelation(extentionName, fields, defaultData);
}

bool ExtendableDataBaseManager::DeleteExtention(QString tableName, QString extentionName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->DeleteRelation(extentionName);
}

bool ExtendableDataBaseManager::SetActiveExtention(QString tableName, QString extentionName)
{
    SetupTable(tableName);
    tableHandlers[tableName]->SetActiveRelation(extentionName);
    return true;
}

int ExtendableDataBaseManager::AddItem(QString tableName, ManagerDataItem item)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->AddItem(item);
}

bool ExtendableDataBaseManager::UpdateItem(QString tableName, ManagerDataItem item)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->UpdateItem(item);
}

bool ExtendableDataBaseManager::DeleteItem(QString tableName, int id)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->DeleteItem(id);
}
