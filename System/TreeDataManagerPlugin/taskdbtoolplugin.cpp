#include "taskdbtoolplugin.h"


TreeDataManagerPlugin::TreeDataManagerPlugin()
{
    dataSource = NULL;

    coreTableStruct.insert("id",         QVariant::Int);
    coreTableStruct.insert("parent",     QVariant::Int);
    coreTableStruct.insert("position",   QVariant::Int);
}

TreeDataManagerPlugin::~TreeDataManagerPlugin()
{

}

bool TreeDataManagerPlugin::SetDataSource(QObject *dataSource)
{
    this->dataSource = qobject_cast<IDataBaseSourcePlugin*>(dataSource);
    if(!this->dataSource)
    {
        qDebug() << dataSource->objectName() << "is not IDataBaseSourcePlugin.";
    }
    qDebug() << "IDataBaseSourcePlugin succesfully set.";
    return true;
}

QString TreeDataManagerPlugin::GetError()
{
    return QString();
}

QList<TreeDataManagerPlugin::TreeItemInfo> TreeDataManagerPlugin::GetTreeData(QString treeName)
{
    qDebug() << "GetTaskTree";
    if(treeName == NULL || treeName == "")
    {
        qDebug() << "Tree name is empty!";
        return QList<TreeItemInfo>();
    }
    treeName = treeName.toLower();
    if(!dataSource)
    {
        qDebug() << "DBManager isnt set!";
        return QList<TreeItemInfo>();
    }
    QString queryStr = QString("CREATE TABLE IF NOT EXISTS %1 (%2)")
            .arg(treeName)
            .arg(GetCoreTableStructString());
    qDebug() << "Creating table" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    qDebug() << query.lastError();
    if(!IsTableRightStructure(treeName))
    {
        qDebug() << "Table" << treeName << "has wrong structure";
        return QList<TreeItemInfo>();
    }

    query = dataSource->ExecuteQuery(QString("select * from %1").arg(treeName));
    QList<TreeItemInfo> taskTree;
    TreeItemInfo buf;
    while (query.next()) {
        buf.id = query.value(0).toInt();
        buf.parent = query.value(1).toInt();
        buf.position = query.value(2).toInt();
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toInt() << query.value(2).toInt();
        for(int i = 3; i < query.size(); i++)
        {
            buf.data.append(query.value(i));
        }
        taskTree.append(buf);
    }
    return taskTree;
}

QMap<QString, QVariant::Type> TreeDataManagerPlugin::GetTreeHeader(QString treeName)
{
    QMap<QString, QVariant::Type> result;
    result.unite(coreTableStruct);

    QList<QString> relationTablesNames = relationsMap[treeName];

    QString structStr = "";
    for(int i = 0; i < relationTablesNames.count(); i++)
    {
        result.unite(relationsDataMap[relationTablesNames[i]]);
    }
}

bool TreeDataManagerPlugin::SetRelation(QString mainName, QString relationName, QMap<QString, QVariant::Type> fields)
{
    qDebug() << "SetRelation";
    QString dataFields = GetTableStructString(fields);
    if(dataFields == "")
    {
        qDebug() << "Can't create relation!";
        return false;
    }

    QString queryStr = QString("CREATE TABLE IF NOT EXISTS %1_%2 (%2)")
            .arg(mainName)
            .arg(relationName)
            .arg(dataFields);
    QSqlQuery queryResult = dataSource->ExecuteQuery(queryStr);
    qDebug() << queryResult.lastError();

    relationsMap[mainName].append(relationName);
    relationsDataMap.insert(relationName, fields);
    return true;
}

bool TreeDataManagerPlugin::DeleteRelation(QString mainName, QString relationName)
{
    qDebug() << "DeleteRelation";
    QString queryStr = QString("DROP TABLE IF EXISTS  %1_%2")
            .arg(mainName)
            .arg(relationName);
    QSqlQuery queryResult = dataSource->ExecuteQuery(queryStr);
    qDebug() << queryResult.lastError();
    relationsMap[mainName].removeOne(relationName);
    relationsDataMap.remove(relationName);
    return true;
}

int TreeDataManagerPlugin::AddItem(QString treeName, TreeItemInfo item)
{
    qDebug() << "Add Task";
    treeName = treeName.toLower();
    QString itemData = "";
//    for(int i = 0; i < item.data.count(); i++)
//    {
//        itemData.append();
//    }

    QString queryStr = QString("insert into %1 values (NULL, '%2', %3, %4)")
            .arg(treeName)
            .arg(item.parent)
            .arg(item.position);

    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    qDebug() << query.lastError();
    return query.lastInsertId().toInt();
}

bool TreeDataManagerPlugin::EditItem(QString treeName, TreeItemInfo item)
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
    qDebug() << query.lastError();
}

bool TreeDataManagerPlugin::DeleteItem(QString treeName, int id)
{
    treeName = treeName.toLower();
    QString queryStr = QString("delete from %1 where id=%2").arg(treeName).arg(id);
    qDebug() << "Delete Task" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    qDebug() << query.lastError();
}

bool TreeDataManagerPlugin::IsTableExists(QString tableName)
{
    // BUG: Not work
    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    return query.size() > 0;
}

bool TreeDataManagerPlugin::IsTableRightStructure(QString tableName)
{
    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    QString name;
    QVariant::Type type;

    while (query.next())
    {
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString() << ": " << query.value(2).toString();
        name = query.value(1).toString();
        type = query.value(2).type();
        if(!coreTableStruct.contains(name) || coreTableStruct[name] != type)
        {
            qDebug() << name << type << "cant exist in right table structure";
            return false;
        }
    }
    return true;
}

QString TreeDataManagerPlugin::GetCoreTableStructString()
{
    QString structStr = "";
    QList<QString> keys = coreTableStruct.keys();
    for(int i = 0; i < keys.count(); i++)
    {
        qDebug() << structStr << keys[i] << coreTableStruct[keys[i]] << QVariant::typeToName(coreTableStruct[keys[i]]);
        structStr.append( QString("%1 %2")
                          .arg(keys[i])
                          .arg( QVariant::typeToName(coreTableStruct[keys[i]]) )
                          );
        if(i == 0) structStr.append(" primary key autoincrement");
        if(i != keys.count()-1) structStr.append(",");
    }
    return structStr;
}

QString TreeDataManagerPlugin::GetTableStructString(QMap<QString, QVariant::Type> tableStruct)
{
    QString structStr = "";
    QList<QString> keys = tableStruct.keys();
    for(int i = 0; i < keys.count(); i++)
    {
        qDebug() << structStr << keys[i] << tableStruct[keys[i]] << QVariant::typeToName(tableStruct[keys[i]]);
        structStr.append(QString("%1 %2")
                         .arg(keys[i])
                         .arg( QVariant::typeToName(tableStruct[keys[i]]) )
                         );
        if(i == 0) structStr.append(" primary key autoincrement");
        if(i != keys.count()-1) structStr.append(",");
    }
    return structStr;
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
