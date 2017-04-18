#include "extendabledatabasemanagerplugin.h"

ExtendableDataBaseManagerPlugin::ExtendableDataBaseManagerPlugin()
{
    dataSource = NULL;
}

ExtendableDataBaseManagerPlugin::~ExtendableDataBaseManagerPlugin()
{

}

void ExtendableDataBaseManagerPlugin::OnAllSetup()
{

}

QString ExtendableDataBaseManagerPlugin::GetLastError()
{
    return lastError;
}

bool ExtendableDataBaseManagerPlugin::SetDataSource(QObject *dataSource)
{
    this->dataSource = qobject_cast<IDataBaseSourcePlugin*>(dataSource);
    if(!this->dataSource)
    {
        qDebug() << dataSource->objectName() << "is not ExtendableDataBaseManagerPlugin.";
    }
    qDebug() << "ExtendableDataBaseManagerPlugin succesfully set.";
    return true;
}

QList<ExtendableDataBaseManagerPlugin::ManagerItemInfo> ExtendableDataBaseManagerPlugin::GetData(QString tableName)
{
    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, tableName);

    return tableHandlers[tableName]->GetData();;
}

QMap<QString, QVariant::Type> ExtendableDataBaseManagerPlugin::GetTreeHeader(QString tableName)
{
    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, tableName);

    return tableHandlers[tableName]->GetHeader();
}

bool ExtendableDataBaseManagerPlugin::SetRelation(QString tableName, QString relationName, QMap<QString, QVariant::Type> fields)
{
    if(!tableHandlers.contains(tableName))
        tableHandlers[tableName] = new TableHandler(dataSource, tableName);

    return tableHandlers[tableName]->SetRelation(relationName, fields);
}

bool ExtendableDataBaseManagerPlugin::DeleteRelation(QString tableName, QString relationName)
{
    return tableHandlers[tableName]->DeleteRelation(relationName);
}

int ExtendableDataBaseManagerPlugin::AddItem(QString tableName, ManagerItemInfo item)
{
    return tableHandlers[tableName]->AddItem(item);
}

bool ExtendableDataBaseManagerPlugin::EditItem(QString tableName, ManagerItemInfo item)
{
    return tableHandlers[tableName]->EditItem(item);
}

bool ExtendableDataBaseManagerPlugin::DeleteItem(QString tableName, int id)
{
    return tableHandlers[tableName]->DeleteItem(id);
}
