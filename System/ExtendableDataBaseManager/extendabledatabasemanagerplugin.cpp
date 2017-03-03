#include "extendabledatabasemanagerplugin.h"

ExtendableDataBaseManagerPlugin::ExtendableDataBaseManagerPlugin()
{
    dataSource = NULL;

    coreTableStruct.append(TableStructItem() = {"id",       QVariant::Int});
    coreTableStruct.append(TableStructItem() = {"parent",   QVariant::Int});
    coreTableStruct.append(TableStructItem() = {"position", QVariant::Int});
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
        qDebug() << dataSource->objectName() << "is not IDataBaseSourcePlugin.";
    }
    qDebug() << "IDataBaseSourcePlugin succesfully set.";
    return true;
}

QList<ExtendableDataBaseManagerPlugin::TreeItemInfo> ExtendableDataBaseManagerPlugin::GetTreeData(QString treeName)
{
    // Is name valid
    qDebug() << "GetTaskTree";
    if(treeName == NULL || treeName == "")
    {
        qDebug() << "Tree name is empty!";
        return QList<TreeItemInfo>();
    }
    treeName = treeName.toLower();

    // Is DataSource set
    if(!dataSource)
    {
        qDebug() << "DBManager isnt set!";
        return QList<TreeItemInfo>();
    }

    // Create query
    QString queryStr = QString("CREATE TABLE IF NOT EXISTS %1 (%2)")
            .arg(treeName)
            .arg(GetTableStructString(coreTableStruct));
    qDebug() << "Creating table" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);

    // Is table has right structure
    if(!IsTableRightStructure(treeName))
    {
        qDebug() << "Table" << treeName << "has wrong structure";
        return QList<TreeItemInfo>();
    }

    // Return tree data
    return GetDataFromTableGroup(treeName);
}

QVector<IExtendableDataBaseManagerPlugin::TableStructItem> ExtendableDataBaseManagerPlugin::GetTreeHeader(QString treeName)
{
    QVector<TableStructItem> result;
    for(int i = 0; i < coreTableStruct.count(); i++)
        result.append(coreTableStruct[i]);

    QList<QString> relationTablesNames = relationsMap[treeName];
    for(int i = 0; i < relationTablesNames.count(); i++)
    {
        QVector<TableStructItem> relationStruct = relationsTableStruct[relationTablesNames[i]];
        for(int i = 0; i < relationStruct.count(); i++)
            result.append(relationStruct[i]);
    }
    return result;
}

bool ExtendableDataBaseManagerPlugin::SetRelation(QString mainName, QString relationName, QVector<TableStructItem> fields)
{
    qDebug() << "SetRelation";
    QString dataFields = GetTableStructString(fields);
    if(dataFields == "")
    {
        qDebug() << "Can't create relation!";
        return false;
    }

    QString queryStr = QString("CREATE TABLE IF NOT EXISTS r_%1_%2 (%2)")
            .arg(mainName)
            .arg(relationName)
            .arg(dataFields);
    QSqlQuery queryResult = dataSource->ExecuteQuery(queryStr);

    relationsMap[mainName].append(relationName);
    relationsTableStruct.insert(relationName, fields);
    return true;
}

bool ExtendableDataBaseManagerPlugin::DeleteRelation(QString mainName, QString relationName)
{
    qDebug() << "DeleteRelation";
    QString queryStr = QString("DROP TABLE IF EXISTS  %1_%2")
            .arg(mainName)
            .arg(relationName);
    QSqlQuery queryResult = dataSource->ExecuteQuery(queryStr);
    relationsMap[mainName].removeOne(relationName);
    relationsTableStruct.remove(relationName);
    return true;
}

int ExtendableDataBaseManagerPlugin::AddItem(QString treeName, TreeItemInfo item)
{
    qDebug() << "Add Task";
    treeName = treeName.toLower();

    QString queryStr = QString("insert into %1 values (NULL, '%2', %3)")
            .arg(treeName)
            .arg(item.parent)
            .arg(item.position);

    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    return query.lastInsertId().toInt();
}

bool ExtendableDataBaseManagerPlugin::EditItem(QString treeName, TreeItemInfo item)
{
    treeName = treeName.toLower();
    QString queryStr = QString("update %1 set name='%3', parent=%4, position=%5 where id=%2")
            .arg(treeName)
            .arg(item.id)
            .arg(item.parent)
            .arg(item.position)
            ;
    qDebug() << "Edit Task" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    if(query.lastError().text() != "")
    {
        lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool ExtendableDataBaseManagerPlugin::DeleteItem(QString treeName, int id)
{
    treeName = treeName.toLower();
    QString queryStr = QString("delete from %1 where id=%2").arg(treeName).arg(id);
    qDebug() << "Delete Task" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    if(query.lastError().text() != "")
    {
        lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool ExtendableDataBaseManagerPlugin::IsTableExists(QString tableName)
{
    // BUG: Not work
    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    return query.size() > 0;
}

bool ExtendableDataBaseManagerPlugin::IsTableRightStructure(QString tableName)
{
    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    QString name;
    QVariant::Type type;

    for(int i = 0; i < coreTableStruct.count(); i++)
    {
        if(!query.next())
        {
            qDebug() << "Too few records!";
            return false;
        }
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString() << ": " << query.value(2).toString();
        name = query.value(1).toString();
        type = query.value(2).type();
        if(coreTableStruct[i].name != name || coreTableStruct[i].type != type)
        {
            qDebug() << name << type << "cant exist in right table structure";
            return false;
        }
    }
    return true;
}

QString ExtendableDataBaseManagerPlugin::GetTableStructString(QVector<TableStructItem> &tableStruct)
{
    QString structStr = "";
    for(int i = 0; i < tableStruct.count(); i++)
    {
        qDebug() << structStr << tableStruct[i].name << tableStruct[i].type
                 << QVariant::typeToName(tableStruct[i].type);
        structStr.append(QString("%1 %2")
                         .arg(tableStruct[i].name)
                         .arg( QVariant::typeToName(tableStruct[i].type) )
                         );
        if(i == 0) structStr.append(" primary key autoincrement");
        if(i != tableStruct.count()-1) structStr.append(",");
    }
    return structStr;
}

QList<IExtendableDataBaseManagerPlugin::TreeItemInfo> ExtendableDataBaseManagerPlugin::GetDataFromTableGroup(QString &treeName)
{
    QString queryStr = "";
    queryStr = QString("select * from %1 ").arg(treeName);
    //left outer join on
    QStringList joinTables = relationsMap[treeName];
    for(int i = 0; i < joinTables.count(); i++)
    {
        queryStr.append( QString("left outer join %2 on %1.id=%2.id ")
                         .arg(treeName)
                         .arg(joinTables[i])
                         );
    }
    qDebug() << queryStr;
//    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
//    QList<TreeItemInfo> taskTree;
//    TreeItemInfo buf;
//    while (query.next()) {
//        buf.id = query.value(0).toInt();
//        buf.parent = query.value(1).toInt();
//        buf.position = query.value(2).toInt();
//        qDebug() << query.value(0).toInt() << ": " << query.value(1).toInt() << query.value(2).toInt();
//        for(int i = 3; i < query.size(); i++)
//        {
//            buf.data.append(query.value(i));
//        }
//        taskTree.append(buf);
//    }
    return QList<TreeItemInfo>();
}

//bool TaskDBToolPlugin::CreateNewTask()
//{
//    query.exec("insert into mapping values (1, 'AAA')");
//    query.exec("insert into mapping values (2, 'BBB')");
//    query.exec("insert into mapping values (3, 'CCC')");
//    query.exec("insert into mapping values (4, 'DDD')");
//    query.exec("insert into mapping values (5, 'EEE')");
//    query.exec("insert into mapping values (6, 'FFF')");
//    query.exec("insert into mapping values (7, 'GGG')");
//    query.exec("select id, name from mapping");
//    while (query.next()) {
//        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString();
//    }
//    qDebug() << "----------" << endl;
//    query.exec("update mapping set name='ZZZ' where id=1");
//    query.exec("select id, name from mapping");
//    while (query.next()) {
//        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString();
//    }
//    qDebug() << "----------" << endl;
//    //query.exec("delete from mapping where id=4");
//    //query.exec("select id, name from mapping");
//    query.exec("pragma table_info(mapping)");
//    while (query.next()) {
//        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString();
//    }
//    query.exec("drop table mapping");
//    return true;
//}
