#include "extendabledamanager.h"

ExtendableDataManager::ExtendableDataManager() :
    PluginBase ()
{
    dataSource = nullptr;
}

ExtendableDataManager::~ExtendableDataManager()
{
    QHash<QString, TableHandler*>::Iterator tablesIter = tableHandlers.begin();

    while(tablesIter != tableHandlers.end())
    {
        delete tablesIter.value();
        ++tablesIter;
    }
}

void ExtendableDataManager::onAllReferencesSet()
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

bool ExtendableDataManager::RegisterExtentionFieldEditor(QString relation, QString field, QWidget *widget)
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

QWidget *ExtendableDataManager::GetExtentionFieldEditor(QString relation, QString field)
{
    if(dataTypeEditorsMap.contains(relation) && dataTypeEditorsMap[relation].contains(field))
        return dataTypeEditorsMap[relation].value(field);

    return nullptr;
}

void ExtendableDataManager::SetupTable(QString &tableName)
{
    tableName = tableName.toLower();

    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, this, tableName);
}

QList<ExtendableDataManager::ManagerDataItem> ExtendableDataManager::GetDataList(QString tableName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetData();
}

IExtendableDataManager::ManagerDataItem ExtendableDataManager::GetDataItem(QString tableName, int id)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetItem(id);
}

void ExtendableDataManager::SetupDataTypeEditors(QString tableName)
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

QAbstractItemModel *ExtendableDataManager::GetDataModel(QString tableName)
{
    SetupTable(tableName);
    QAbstractItemModel *itemModel = tableHandlers[tableName]->GetModel();
    SetupDataTypeEditors(tableName);
    return itemModel;
}

QAbstractItemModel *ExtendableDataManager::GetDataModel(QVector<QPair<QString, QString> > dataModelFields)
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

QAbstractItemModel * ExtendableDataManager::CreateProxy(QVector<QPair<QString, QString> > &dataModelFields)
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

QMap<QString, QVariant::Type> ExtendableDataManager::GetTableHeader(QString tableName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->GetHeader();
}

bool ExtendableDataManager::AddExtention(QString tableName, QString extentionName,
        QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->SetRelation(extentionName, fields, defaultData);
}

bool ExtendableDataManager::DeleteExtention(QString tableName, QString extentionName)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->DeleteRelation(extentionName);
}

bool ExtendableDataManager::SetActiveExtention(QString tableName, QString extentionName)
{
    SetupTable(tableName);
    tableHandlers[tableName]->SetActiveRelation(extentionName);
    return true;
}

int ExtendableDataManager::AddItem(QString tableName, ManagerDataItem item)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->AddItem(item);
}

bool ExtendableDataManager::UpdateItem(QString tableName, ManagerDataItem item)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->UpdateItem(item);
}

bool ExtendableDataManager::DeleteItem(QString tableName, int id)
{
    SetupTable(tableName);
    return tableHandlers[tableName]->DeleteItem(id);
}
