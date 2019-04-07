#include "tablehandler.h"

TableHandler::TableHandler(IDataBase *dataSource, IExtendableDataManager *dataManager, QString tableName)
{
    this->dataSource = dataSource;
    this->dataManager = dataManager;
    this->tableName = tableName;
    itemModel = nullptr;
    CreateTable();
}

TableHandler::~TableHandler()
{
    if(itemModel)
        delete itemModel;
}

bool TableHandler::HasRelation(QString relation)
{
    return relationTablesStructs.contains(relation);
}

bool TableHandler::CreateTable()
{
    // Is name valid?
    if(tableName == nullptr || tableName == "")
    {
        qDebug() << "Tree name is empty!";
        return false;
    }

    coreTableStruct = {{"id", QVariant::Int}};

    if(IsTableExists(tableName))
    {
        // Is table has right structure.
        if(!IsTableHasRightStructure(tableName, coreTableStruct))
        {
            qDebug() << "Table" << tableName << "has wrong structure";
            return false;
        }
    }
    else
    {
        // Create table.
        QString queryStr = QString("CREATE TABLE IF NOT EXISTS %1 (%2)")
                           .arg(tableName)
                           .arg(GetHeaderString(coreTableStruct));
        QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    }

    CombineWholeTableStruct();
    isCreated = true;
    return true;
}

bool TableHandler::SetRelation(QString relationName, TableStructMap fields, QVector<QVariant> defaultData)
{
    if(relationName == "")
    {
        qDebug() << "Relation name is empty!";
        return false;
    }

    // This kind of magic trick with "id" field made only for setting proper table header
    // Because for setting relation I need "id" field in table but for operating with data
    // it only complicates everything
    fields.insert("id", QVariant::Int);                 // <-- Magic
    relationName = relationName.toLower();
    QString databaseRelationName = QString("r_%1_%2")
                                   .arg(tableName)
                                   .arg(relationName);
    bool tableCreationNeeded = true;

    if(IsTableExists(databaseRelationName))
    {
        tableCreationNeeded = false;

        if(!IsTableHasRightStructure(databaseRelationName, fields))
        {
            tableCreationNeeded = true;
            DeleteRelation(relationName);
        }
    }

    if(tableCreationNeeded)
    {
        QString dataFields = GetHeaderString(fields, true);

        if(dataFields == "")
        {
            qDebug() << "Can't create relation!";
            return false;
        }

        QString queryStr = QString("CREATE TABLE IF NOT EXISTS %1 (%2)")
                           .arg(databaseRelationName)
                           .arg(dataFields);
        QSqlQuery queryResult = dataSource->ExecuteQuery(queryStr);
    }

    fields.remove("id");                                // <-- Trick
    relationTablesStructs.insert(relationName, fields);
    relationsDefaultData.insert(relationName, defaultData);

    if(itemModel)
        itemModel->AttachRelation(relationName, fields, defaultData);

    return true;
}

void TableHandler::SetActiveRelation(QString relationName)
{
    InstallModel();

    if(itemModel)
        itemModel->SetActiveRelation(relationName);
}

void TableHandler::SetDataTypeEditor(QString dataChunk, QString fieldName, QWidget *widget)
{
    if(itemModel)
        itemModel->SetDataTypeEditor(dataChunk, fieldName, widget);
}

bool TableHandler::DeleteRelation(QString relationName)
{
    qDebug() << "DeleteRelation";
    relationName = relationName.toLower();
    QString queryStr = QString("DROP TABLE  r_%1_%2")
                       .arg(tableName)
                       .arg(relationName);
    QSqlQuery queryResult = dataSource->ExecuteQuery(queryStr);
    relationTablesStructs.remove(relationName);
    CombineWholeTableStruct();
    return true;
}

TableHandler::ManagerDataItem TableHandler::GetItem(int id)
{
    QString queryStr = QString("SELECT %1.id").arg(tableName);
    QStringList joinTables = relationTablesStructs.keys();
    QString tableRefPrefix = QString("r_%1_").arg(tableName);

    for(int i = 0; i < joinTables.count(); ++i)
    {
        queryStr.append(",");
        queryStr.append( GetFieldsNames(tableRefPrefix+joinTables[i], relationTablesStructs[joinTables[i]]) );
    }

    queryStr.append( QString(" FROM %1 ").arg(tableName) );
    queryStr.append( QString(" ON %1.id = %2 ").arg(tableName).arg(id) );

    for(int i = 0; i < joinTables.count(); i++)
    {
        queryStr.append(QString(" LEFT OUTER JOIN r_%1_%2 ON %1.id = r_%1_%2.id")
                        .arg(tableName)
                        .arg(joinTables[i]));
    }

    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    ManagerDataItem buf;
    QString bufStr;
    int queryFieldNum;
    bufStr = "";
    queryFieldNum = 0;
    buf.id = query.value(queryFieldNum).toInt();
    ++queryFieldNum;

    for(int i = 0; i < joinTables.count(); ++i)
    {
        qDebug() << "> " << joinTables[i];

        for(int j = 0; j < relationTablesStructs[joinTables[i]].count(); ++j)
        {
            qDebug() << query.value(queryFieldNum);
            buf.dataChunks[joinTables[i]].append( query.value(queryFieldNum) );
            ++queryFieldNum;
        }
    }

    return buf;
}

QList<IExtendableDataManager::ManagerDataItem> TableHandler::GetData()
{
    QString queryStr = QString("SELECT %1.id").arg(tableName);
    QStringList joinTables = relationTablesStructs.keys();
    QString tableRefPrefix = QString("r_%1_").arg(tableName);

    for(int i = 0; i < joinTables.count(); ++i)
    {
        queryStr.append(",");
        queryStr.append( GetFieldsNames(tableRefPrefix+joinTables[i], relationTablesStructs[joinTables[i]]) );
    }

    queryStr.append( QString(" FROM %1 ").arg(tableName) );

    for(int i = 0; i < joinTables.count(); i++)
    {
        queryStr.append(QString(" LEFT OUTER JOIN r_%1_%2 ON %1.id = r_%1_%2.id")
                        .arg(tableName)
                        .arg(joinTables[i]));
    }

    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    QList<ManagerDataItem> itemInfoList;
    ManagerDataItem buf;
    QString bufStr;
    int queryFieldNum;

    while (query.next())
    {
        bufStr = "";
        queryFieldNum = 0;
        buf.id = query.value(queryFieldNum).toInt();
        ++queryFieldNum;

        for(int i = 0; i < joinTables.count(); ++i)
        {
            for(int j = 0; j < relationTablesStructs[joinTables[i]].count(); ++j)
            {
                buf.dataChunks[joinTables[i]].append( query.value(queryFieldNum) );
                ++queryFieldNum;
            }
        }

        itemInfoList.append(buf);
        buf.dataChunks.clear();
    }

    return itemInfoList;
}

void TableHandler::InstallModel()
{
    if(itemModel)
        return;

    itemModel = new ExtendableItemModel(tableName, dataManager);
    auto defaultDataIter = relationsDefaultData.begin();
    auto relationStructIter = relationTablesStructs.begin();

    while(defaultDataIter != relationsDefaultData.end())
    {
        itemModel->AttachRelation(defaultDataIter.key(), relationStructIter.value(), defaultDataIter.value());
        ++defaultDataIter;
        ++relationStructIter;
    }

    itemModel->LoadData();
}

QAbstractItemModel *TableHandler::GetModel()
{
    InstallModel();
    return itemModel;
}

int TableHandler::AddItem(ManagerDataItem item)
{
    qDebug() << "AddItem";
    QString queryStr = QString("INSERT INTO %1 (id) VALUES (NULL)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    int lastId = query.lastInsertId().toInt();
    QStringList joinTables = item.dataChunks.keys();
    qDebug() << joinTables.count();

    for(int i = 0; i < joinTables.count(); i++)
    {
        QString valuesString = GetInsertValuesString(relationTablesStructs[joinTables[i]], lastId, item.dataChunks[joinTables[i]]);

        if(valuesString != "")
        {
            queryStr = "";
            queryStr.append(QString("INSERT INTO r_%1_%2 %3")
                            .arg(tableName)
                            .arg(joinTables[i])
                            .arg(valuesString)
                           );
            dataSource->ExecuteQuery(queryStr);
        }
        else
        {
            qDebug() << "Empty string!";
        }
    }

    return lastId;
}

bool TableHandler::UpdateItem(ManagerDataItem item)
{
    qDebug() << "AddItem";
    QString queryStr;
    QStringList joinTables = item.dataChunks.keys();
    qDebug() << joinTables.count();

    for(int i = 0; i < joinTables.count(); i++)
    {
        TableStructMap *tableStruct = &relationTablesStructs[joinTables[i]];
        QString valuesString = GetUpdateValuesString(*tableStruct, item.id);

        if(valuesString != "")
        {
            queryStr = "";
            queryStr.append(QString("UPDATE r_%1_%2 SET %3")
                            .arg(tableName)
                            .arg(joinTables[i])
                            .arg(valuesString) );
            qDebug() << queryStr;
            QList<QString> list = tableStruct->keys();

            for(int i = 0; i < list.count(); ++i)
                list[i] = ":" + list[i].toUpper();

            QList<QVariant> values = item.dataChunks[joinTables[i]].toList();
            dataSource->ExecuteQuery(queryStr, &list, &values);
        }
        else
        {
            qDebug() << "Empty string!";
        }
    }

    return true;
}

bool TableHandler::DeleteItem(int id)
{
    QString queryStr = QString("delete from %1 where id=%2").arg(tableName).arg(id);
    qDebug() << "Delete Task" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    return true;
}

TableHandler::TableStructMap TableHandler::GetHeader()
{
    return wholeTableStruct;
}

QVector<QVariant> TableHandler::GetRelationDefaultData(QString relationName)
{
    if(!relationsDefaultData.contains(relationName))
        return QVector<QVariant>();

    return relationsDefaultData[relationName];
}

QString TableHandler::GetHeaderString(TableStructMap &tableStruct, bool createRelation)
{
    QString structStr = "";
    TableStructMap::Iterator i = tableStruct.begin();
    TableStructMap::Iterator lastElement = --tableStruct.end();

    while(i != tableStruct.end())
    {
        QString typeNameString = dataBaseTypesNames.contains(i.value()) ?
                                 dataBaseTypesNames[i.value()] : QVariant::typeToName(i.value());
        structStr.append(QString("%1 %2").arg(i.key()).arg(typeNameString));

        if(i.key() == "id")
        {
            QString idAppendix = createRelation ?
                                 QString(" REFERENCES %1(id) ON DELETE CASCADE").arg(tableName) :
                                 " PRIMARY KEY AUTOINCREMENT";
            structStr.append(idAppendix);
        }

        if(i != lastElement)
            structStr.append(",");

        ++i;
    }

    return structStr;
}

QString TableHandler::GetFieldsNames(QString tableName, TableHandler::TableStructMap &tableStruct, bool includeId)
{
    QString structStr = "";
    TableStructMap::Iterator i = tableStruct.begin();
    TableStructMap::Iterator lastElement = --tableStruct.end();

    while(i != tableStruct.end())
    {
        if(i.key() != "id" || includeId)
            structStr.append(QString("%1.%2").arg(tableName).arg(i.key()));

        if(i != lastElement)
            structStr.append(",");

        ++i;
    }

    return structStr;
}

QString TableHandler::GetInsertValuesString(TableStructMap &tableStruct, int id, QVector<QVariant> &itemData)
{
    if(tableStruct.count() != itemData.count())
    {
        qDebug() << "Wrong size" << tableStruct.count() << itemData.count();
        return QString();
    }

    QString fieldNamesStr = "(id, ";
    QString valuesStr = QString("(%1, ").arg(QString::number(id));
    TableStructMap::Iterator structIter = tableStruct.begin();
    TableStructMap::Iterator lastElement = --tableStruct.end();
    QVector<QVariant>::Iterator dataIter = itemData.begin();

    while(structIter != tableStruct.end())
    {
        fieldNamesStr.append(structIter.key());
        QString buf;

        if(dataIter->type() == QVariant::String || dataIter->type() == QVariant::ByteArray)
            buf = QString("'%1'").arg(dataIter->toString());
        else
            buf = dataIter->toString();

        valuesStr.append(buf);

        if(structIter != lastElement)
        {
            fieldNamesStr.append(",");
            valuesStr.append(",");
        }
        else
        {
            fieldNamesStr.append(")");
            valuesStr.append(")");
        }

        ++structIter;
        ++dataIter;
    }

    return QString("%1 VALUES %2").arg(fieldNamesStr).arg(valuesStr);
}

QString TableHandler::GetUpdateValuesString(TableHandler::TableStructMap &tableStruct, int id)
{
    QString resultStr = "";
    TableStructMap::Iterator structIter = tableStruct.begin();
    TableStructMap::Iterator lastElement = --tableStruct.end();

    while(structIter != tableStruct.end())
    {
        resultStr.append(structIter.key()).append("=");

        if(structIter.value() == QVariant::String || structIter.value() == QVariant::ByteArray)
            resultStr.append(QString(":%1").arg(structIter.key().toUpper()));
        else
            resultStr.append(":").append(structIter.key().toUpper());

        if(structIter != lastElement)
            resultStr.append(",");

        ++structIter;
    }

    resultStr.append(" where id=").append(QString::number(id));
    return resultStr;
}

QString TableHandler::GetUpdateValuesString(TableHandler::TableStructMap &tableStruct, int id, QVector<QVariant> &itemData)
{
    if(tableStruct.count() != itemData.count())
    {
        qDebug() << "Wrong size" << tableStruct.count() << itemData.count();
        return QString();
    }

    QString resultStr = "";
    TableStructMap::Iterator structIter = tableStruct.begin();
    TableStructMap::Iterator lastElement = --tableStruct.end();
    QVector<QVariant>::Iterator dataIter = itemData.begin();

    while(structIter != tableStruct.end())
    {
        resultStr.append(structIter.key()).append("=");

        if(dataIter->type() == QVariant::String || dataIter->type() == QVariant::ByteArray)
            resultStr.append(QString("'%1'").arg(dataIter->toString()));
        else
            resultStr.append(dataIter->toString());

        if(structIter != lastElement)
            resultStr.append(",");

        ++structIter;
        ++dataIter;
    }

    resultStr.append(" where id=").append(QString::number(id));
    return resultStr;
}

bool TableHandler::IsTableExists(QString tableName)
{
    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    return query.next();
}

void TableHandler::CombineWholeTableStruct()
{
    wholeTableStruct.clear();
    wholeTableStruct.unite(relationTablesStructs[tableName]);
    auto i = relationTablesStructs.begin();

    while(i != relationTablesStructs.end())
    {
        wholeTableStruct.unite(i.value());
        ++i;
    }
}

bool TableHandler::IsTableHasRightStructure(QString tableName, TableStructMap &tableStruct)
{
    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    QString name;
    QVariant::Type type;
    auto iter = tableStruct.begin();

    while(iter != tableStruct.end())
    {
        if(!query.next())
        {
            qCritical("Too few records!");
            return true;
        }

        name = query.value(1).toString();
        type = dataBaseTypesNames.key(query.value(2).toString());

        if(iter.key() != name || iter.value() != type)
        {
            qDebug() << name << type << "is new field!";
            return false;
        }

        ++iter;
    }

    return true;
}
