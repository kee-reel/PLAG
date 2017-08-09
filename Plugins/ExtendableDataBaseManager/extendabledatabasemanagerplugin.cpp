#include "extendabledatabasemanagerplugin.h"

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
    if(pluginInfo->Meta->InterfaceName == "IDATABASESOURCEPLUGIN")
    {
        this->dataSource = qobject_cast<IDataBaseSourcePlugin*>(pluginInfo->Instance);
        if(!this->dataSource)
        {
            qDebug() << pluginInfo->Meta->Name << "is not ExtendableDataBaseManagerPlugin.";
        }
        qDebug() << "ExtendableDataBaseManagerPlugin succesfully set.";
    }
}

void ExtendableDataBaseManagerPlugin::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

//bool ExtendableDataBaseManagerPlugin::AddDataSource(QObject *dataSource)
//{
//    this->dataSource = qobject_cast<IDataBaseSourcePlugin*>(dataSource);
//    if(!this->dataSource)
//    {
//        qDebug() << dataSource->objectName() << "is not ExtendableDataBaseManagerPlugin.";
//    }
//    qDebug() << "ExtendableDataBaseManagerPlugin succesfully set.";
//    return true;
//}

QList<ExtendableDataBaseManagerPlugin::ManagerDataItem> ExtendableDataBaseManagerPlugin::GetDataList(QString tableName)
{
    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, this, tableName);
    return tableHandlers[tableName]->GetData();
}

IExtendableDataBaseManager::ManagerDataItem ExtendableDataBaseManagerPlugin::GetDataItem(QString tableName, int id)
{
    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, this, tableName);
    return tableHandlers[tableName]->GetItem(id);
}

QAbstractItemModel *ExtendableDataBaseManagerPlugin::GetDataModel(QString tableName)
{
    if(!tableHandlers.contains(tableName))
        return false;
    return tableHandlers[tableName]->GetModel();
}

QMap<QString, QVariant::Type> ExtendableDataBaseManagerPlugin::GetTableHeader(QString tableName)
{
    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, this, tableName);
    return tableHandlers[tableName]->GetHeader();
}

bool ExtendableDataBaseManagerPlugin::SetRelation(QString tableName, QString relationName, QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData)
{
    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, this, tableName);
    return tableHandlers[tableName]->SetRelation(relationName, fields, defaultData);
}

bool ExtendableDataBaseManagerPlugin::DeleteRelation(QString tableName, QString relationName)
{
    if(!tableHandlers.contains(tableName))
        return false;
    return tableHandlers[tableName]->DeleteRelation(relationName);
}

bool ExtendableDataBaseManagerPlugin::SetActiveRelation(QString tableName, QString relationName)
{
    if(!tableHandlers.contains(tableName))
        return false;
    tableHandlers[tableName]->SetActiveRelation(relationName);
    return true;
}

int ExtendableDataBaseManagerPlugin::AddItem(QString tableName, ManagerDataItem item)
{
    return tableHandlers[tableName]->AddItem(item);
}

bool ExtendableDataBaseManagerPlugin::EditItem(QString tableName, ManagerDataItem item)
{
    return tableHandlers[tableName]->EditItem(item);
}

bool ExtendableDataBaseManagerPlugin::DeleteItem(QString tableName, int id)
{
    return tableHandlers[tableName]->DeleteItem(id);
}
