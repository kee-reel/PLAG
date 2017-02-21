#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include <QString>
#include <QtSql>
#include <QObject>

#include "itaskdbtoolplugin.h"

class TaskDataManagerPlugin : public QObject, ITaskDataManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TaskDBToolPlugin" FILE "PluginMeta.json")
    Q_INTERFACES(IDataManagerPlugin ITaskDataManagerPlugin)

    // IDataManagerPlugin interface
public:
    virtual bool SetDataSource(QObject *dataSource);
    virtual QString GetError();

    // ITaskDBToolPlugin interface
public:
    virtual QList<TaskInfo> GetTaskTree(QString treeName);
    virtual int AddTask(QString treeName, TaskInfo task);
    virtual bool EditTask(QString treeName, TaskInfo task);
    virtual bool DeleteTask(QString treeName, int id);

public:
    TaskDataManagerPlugin();
    ~TaskDataManagerPlugin();

private:
    IDataBaseSourcePlugin* dataSource;
    struct ColumnInfo{
        QString name;
        QString type;
    };
    QVector<ColumnInfo> tableStruct;

    bool IsTableExists(QString tableName);
    bool IsTableRightStructure(QString tableName);
    QString GetStringStruct();
    ColumnInfo CombineFormInfo(QString name, QString type);
};

#endif // TASKDBTOOLPLUGIN_H
