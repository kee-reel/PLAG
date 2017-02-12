#include "taskdbtoolplugin.h"


TaskDataManagerPlugin::TaskDataManagerPlugin()
{
    dataSource = NULL;
    tableStruct.insert("id",        "int");
    tableStruct.insert("name",      "varchar");
    tableStruct.insert("level",     "int");
    tableStruct.insert("parent",    "int");
    tableStruct.insert("position",  "int");
}

TaskDataManagerPlugin::~TaskDataManagerPlugin()
{

}

bool TaskDataManagerPlugin::SetDataSource(QObject *dataSource)
{
    this->dataSource = qobject_cast<IDataBaseSourcePlugin*>(dataSource);
    if(!this->dataSource)
    {
        qDebug() << dataSource->objectName() << "is not IDataBaseSourcePlugin.";
    }
    qDebug() << "IDataBaseSourcePlugin succesfully set.";
    return true;
}

QString TaskDataManagerPlugin::GetError()
{
    return QString();
}

ITaskDataManagerPlugin::TaskInfo* TaskDataManagerPlugin::GetTaskTree(QString treeName)
{
    qDebug() << "GetTaskTree";
    if(treeName == NULL || treeName == "")
    {
        qDebug() << "Tree name is empty!";
        return NULL;
    }
    treeName = treeName.toLower();
    if(!dataSource)
    {
        qDebug() << "DBManager isnt set!";
        return NULL;
    }
    qDebug() << "Creating table" << treeName;
    QSqlQuery queryRes =
            dataSource->ExecuteQuery(QString("CREATE TABLE IF NOT EXISTS %1 (%2)")
                                    .arg(treeName)
                                    .arg(GetStringStruct()));
    qDebug() << IsTableExists(treeName);
    if(!IsTableRightStructure(treeName))
    {
        qDebug() << "Table" << treeName << "has wrong structure";
        return NULL;
    }

    return NULL;
}

bool TaskDataManagerPlugin::AddTask(ITaskDataManagerPlugin::TaskInfo *taskTree)
{
    QString queryStr = "";
    //QSqlQuery *query = DBManager->ExecuteQuery(queryStr);
}

bool TaskDataManagerPlugin::EditTask(ITaskDataManagerPlugin::TaskInfo *taskTree)
{
    QString queryStr = "";
    //QSqlQuery *query = DBManager->ExecuteQuery(queryStr);
}

bool TaskDataManagerPlugin::DeleteTask(ITaskDataManagerPlugin::TaskInfo *taskTree)
{
    QString queryStr = "";
    //QSqlQuery *query = DBManager->ExecuteQuery(queryStr);
}

bool TaskDataManagerPlugin::IsTableExists(QString tableName)
{
    // BUG: Not work
    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    return query.size() > 0;
}

bool TaskDataManagerPlugin::IsTableRightStructure(QString tableName)
{
    QString queryStr = QString("pragma table_info(%1)").arg(tableName);
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);

    QString key, value;
    while (query.next())
    {
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString() << ": " << query.value(2).toString();
        key = query.value(1).toString();
        value = query.value(2).toString();
        if(!tableStruct.contains(key) || tableStruct[key] != value)
        {
            qDebug() << key << value << "cant exist in right table structure";
            return false;
        }
    }
    return true;
}

QString TaskDataManagerPlugin::GetStringStruct()
{
    QString structStr = "";
    foreach (QString key, tableStruct.keys()) {
        structStr.append(QString("%1 %2,").arg(key).arg(tableStruct[key]));
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
