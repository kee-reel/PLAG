#include "taskdbtoolplugin.h"


TaskDataManagerPlugin::TaskDataManagerPlugin()
{
    dataSource = NULL;

    tableStruct.append(CombineFormInfo("id",        "integer"));
    tableStruct.append(CombineFormInfo("name",      "varchar"));
    //tableStruct.append(CombineFormInfo("level",     "integer"));
    tableStruct.append(CombineFormInfo("parent",    "integer"));
    tableStruct.append(CombineFormInfo("position",  "integer"));
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

QList<ITaskDataManagerPlugin::TaskInfo> TaskDataManagerPlugin::GetTaskTree(QString treeName)
{
    qDebug() << "GetTaskTree";
    if(treeName == NULL || treeName == "")
    {
        qDebug() << "Tree name is empty!";
        return QList<ITaskDataManagerPlugin::TaskInfo>();
    }
    treeName = treeName.toLower();
    if(!dataSource)
    {
        qDebug() << "DBManager isnt set!";
        return QList<ITaskDataManagerPlugin::TaskInfo>();
    }
    QString queryStr = QString("CREATE TABLE IF NOT EXISTS %1 (%2)")
            .arg(treeName)
            .arg(GetStringStruct());
    qDebug() << "Creating table" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    qDebug() << query.lastError();
    if(!IsTableRightStructure(treeName))
    {
        qDebug() << "Table" << treeName << "has wrong structure";
        return QList<ITaskDataManagerPlugin::TaskInfo>();
    }

    query = dataSource->ExecuteQuery(QString("select * from %1").arg(treeName));
    QList<TaskInfo> taskTree;
    TaskInfo buf;
    while (query.next()) {
        buf.id = query.value(0).toInt();
        buf.name = query.value(1).toString();
        //buf.level = query.value(2).toInt();
        buf.parent = query.value(2).toInt();
        buf.position = query.value(3).toInt();
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString()
                    << query.value(2).toInt() << ": " << query.value(3).toInt();
        taskTree.append(buf);
    }
    return taskTree;
}

int TaskDataManagerPlugin::AddTask(QString treeName, ITaskDataManagerPlugin::TaskInfo task)
{
    qDebug() << "Add Task";
    treeName = treeName.toLower();
    QString queryStr = QString("insert into %1 values (NULL, '%2', %3, %4)")
            .arg(treeName)
            .arg(task.name)
            //.arg(task.level)
            .arg(task.parent)
            .arg(task.position)
            ;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    qDebug() << query.lastError();
    return query.lastInsertId().toInt();
}

bool TaskDataManagerPlugin::EditTask(QString treeName, ITaskDataManagerPlugin::TaskInfo task)
{
    treeName = treeName.toLower();
    QString queryStr = QString("update %1 set name='%3', parent=%4, position=%5 where id=%2")
            .arg(treeName)
            .arg(task.id)
            .arg(task.name)
            //.arg(task.level)
            .arg(task.parent)
            .arg(task.position)
            ;
    qDebug() << "Edit Task" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    qDebug() << query.lastError();
}

bool TaskDataManagerPlugin::DeleteTask(QString treeName, int id)
{
    treeName = treeName.toLower();
    QString queryStr = QString("delete from %1 where id=%2").arg(treeName).arg(id);
    qDebug() << "Delete Task" << queryStr;
    QSqlQuery query = dataSource->ExecuteQuery(queryStr);
    qDebug() << query.lastError();
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
    QString name, type;
    QMap<QString, QString> fieldNamesCheckInfo;
    for(int i = 0; i < tableStruct.count(); i++)
        fieldNamesCheckInfo.insert(tableStruct[i].name, tableStruct[i].type);

    while (query.next())
    {
        qDebug() << query.value(0).toInt() << ": " << query.value(1).toString() << ": " << query.value(2).toString();
        name = query.value(1).toString();
        type = query.value(2).toString();
        if(!fieldNamesCheckInfo.contains(name) || fieldNamesCheckInfo[name] != type)
        {
            qDebug() << name << type << "cant exist in right table structure";
            return false;
        }
    }
    return true;
}

QString TaskDataManagerPlugin::GetStringStruct()
{
    QString structStr = "";
    QString valuesStr;

    for(int i = 0; i < tableStruct.count(); i++)
    {
        valuesStr = "%1 %2";
        if(i == 0) valuesStr.append(" primary key autoincrement");
        if(i != tableStruct.count()-1) valuesStr.append(",");
        structStr.append(valuesStr.arg(tableStruct[i].name).arg(tableStruct[i].type));
    }
    return structStr;
}

TaskDataManagerPlugin::ColumnInfo TaskDataManagerPlugin::CombineFormInfo(QString name, QString type)
{
    TaskDataManagerPlugin::ColumnInfo info = {name, type};
    return info;
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
