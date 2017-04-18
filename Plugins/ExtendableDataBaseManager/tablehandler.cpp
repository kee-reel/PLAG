#include "tablehandler.h"

TableHandler::TableHandler(IDataBaseSourcePlugin *dataSource, QString tableName)
{
    this->dataSource = dataSource;
    this->tableName = tableName;

    dataBaseTypesNames.insert(QVariant::Int,    "INTEGER");
    dataBaseTypesNames.insert(QVariant::String, "VARCHAR");
    dataBaseTypesNames.insert(QVariant::ByteArray, "BLOB");

    coreTableStruct.insert("id", QVariant::Int);

    CombineWholeTableStruct();

    if(tableName == "")
        isCreated = false;
    else
        CreateTable();
}

bool TableHandler::CreateTable()
{
    // Is name valid
    qDebug() << "Create new table" << tableName;
    if(tableName == NULL || tableName == "")
    {
        qDebug() << "Tree name is empty!";
        return false;
    }
    tableName = tableName.toLower();

    // Is DataSource set
    if(!dataSource)
    {
        qDebug() << "DBManager isnt set!";
        return false;
    }

    // Create query
    QString queryStr = QString("CREATE TABLE IF NOT EXISTS %1 (%2)")
            .arg(tableName)
            .arg(GetHeaderString(coreTableStruct));
    qDebug() << "Creating table" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);

    // Is table has right structure
//    if(!IsTableRightStructure(tableName))
//    {
//        qDebug() << "Table" << tableName << "has wrong structure";
//        return false;
//    }

    isCreated = true;
    return true;
}

bool TableHandler::SetRelation(QString relationName, TableStructMap fields)
{
    qDebug() << "SetRelation";
    if(relationName == "")
    {
        qDebug() << "Relation name is empty!";
        return false;
    }

    fields.insert("id", QVariant::Int);
    QString dataFields = GetHeaderString(fields, true);
    if(dataFields == "")
    {
        qDebug() << "Can't create relation!";
        return false;
    }

    relationName = relationName.toLower();
    QString queryStr = QString("CREATE TABLE IF NOT EXISTS r_%1_%2 (%3)")
            .arg(tableName)
            .arg(relationName)
            .arg(dataFields);
    QSqlQuery queryResult = dataSource->ExecuteQuery(queryStr);

    fields.remove("id");
    relationTableStructs.insert(relationName, fields);
    return true;
}

bool TableHandler::DeleteRelation(QString relationName)
{
    qDebug() << "DeleteRelation";
    relationName = relationName.toLower();
    QString queryStr = QString("DROP TABLE IF EXISTS  %1_%2")
            .arg(tableName)
            .arg(relationName);
    QSqlQuery queryResult = dataSource->ExecuteQuery(queryStr);
    relationTableStructs.remove(relationName);
    CombineWholeTableStruct();
    return true;
}

QList<IExtendableDataBaseManagerPlugin::ManagerItemInfo> TableHandler::GetData()
{
    QString queryStr = QString("SELECT %1.id").arg(tableName);
    QStringList joinTables = relationTableStructs.keys();
    QString tableRefPrefix = QString("r_%1_").arg(tableName);
    for(int i = 0; i < joinTables.count(); ++i)
    {
        queryStr.append(",");
        queryStr.append( GetFieldsNames(tableRefPrefix+joinTables[i], relationTableStructs[joinTables[i]]) );
    }
    queryStr.append( QString(" FROM %1 ").arg(tableName) );
    for(int i = 0; i < joinTables.count(); i++)
    {
        queryStr.append(QString(" LEFT OUTER JOIN r_%1_%2 ON %1.id = r_%1_%2.id")
                        .arg(tableName)
                        .arg(joinTables[i]));
    }
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    QList<ManagerItemInfo> itemInfoList;
    ManagerItemInfo buf;

    QString bufStr;
    int queryFieldNum;

    while (query.next()) {
        qDebug() << endl << ">> Query result";
        bufStr = "";
        queryFieldNum = 0;

        qDebug() << query.value(queryFieldNum);
        buf.id = query.value(queryFieldNum).toInt();
        ++queryFieldNum;

        for(int i = 0; i < joinTables.count(); ++i)
        {
            qDebug() << "> " << joinTables[i];
            for(int j = 0; j < relationTableStructs[joinTables[i]].count(); ++j)
            {
                qDebug() << query.value(queryFieldNum);
                buf.dataChunks[joinTables[i]].append( query.value(queryFieldNum) );
                ++queryFieldNum;
            }
        }

        itemInfoList.append(buf);
        buf.dataChunks.clear();
    }
    return itemInfoList;
}

int TableHandler::AddItem(ManagerItemInfo item)
{
    qDebug() << "AddItem";

    QString queryStr = QString("INSERT INTO %1 (id) VALUES (NULL)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    int lastId = query.lastInsertId().toInt();

    QStringList joinTables = item.dataChunks.keys();
    qDebug() << joinTables.count();
    for(int i = 0; i < joinTables.count(); i++)
    {
        QString valuesString = GetInsertValuesString(relationTableStructs[joinTables[i]], lastId, item.dataChunks[joinTables[i]]);
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

bool TableHandler::EditItem(ManagerItemInfo item)
{
    qDebug() << "AddItem";

    QString queryStr;

    QStringList joinTables = item.dataChunks.keys();
    qDebug() << joinTables.count();
    for(int i = 0; i < joinTables.count(); i++)
    {
        TableStructMap *tableStruct = &relationTableStructs[joinTables[i]];
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

QString TableHandler::GetHeaderString(TableStructMap &tableStruct, bool createRelation)
{
    QString structStr = "";
    TableStructMap::Iterator i = tableStruct.begin();
    TableStructMap::Iterator lastElement = --tableStruct.end();
    while(i != tableStruct.end())
    {
        QString typeNameString = dataBaseTypesNames.contains(i.value()) ? dataBaseTypesNames[i.value()] : QVariant::typeToName(i.value());
        structStr.append(QString("%1 %2").arg(i.key()).arg(typeNameString));
        if(i.key() == "id")
        {
            QString idAppendix = createRelation ?
                        QString(" REFERENCES %1(id) ON DELETE CASCADE").arg(tableName) :
                        " PRIMARY KEY AUTOINCREMENT";
            structStr.append(idAppendix);
        }
        if(i != lastElement) structStr.append(",");
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
        if(i != lastElement) structStr.append(",");
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
    // BUG: Not work
    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    return query.size() > 0;
}

void TableHandler::CombineWholeTableStruct()
{
    wholeTableStruct.clear();
    wholeTableStruct.unite(coreTableStruct);

    QMap<QString, TableStructMap>::Iterator i = relationTableStructs.begin();
    while(i != relationTableStructs.end())
    {
        wholeTableStruct.unite(i.value());
        ++i;
    }
}

//bool TableHandler::IsTableRightStructure(QString tableName)
//{
//    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
//    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
//    QString name;
//    QVariant::Type type;

//    for(int i = 0; i < coreTableStruct.count(); i++)
//    {
//        if(!query.next())
//        {
//            qDebug() << "Too few records!";
//            return false;
//        }
//        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString() << ": " << query.value(2).toString();
//        name = query.value(1).toString();
//        type = query.value(2).type();
//        if(coreTableStruct[i].name != name || coreTableStruct[i].type != type)
//        {
//            qDebug() << name << type << "cant exist in right table structure";
//            return false;
//        }
//    }
//    return true;
//}
