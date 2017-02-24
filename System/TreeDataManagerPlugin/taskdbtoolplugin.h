#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include <QString>
#include <QtSql>
#include <QObject>

#include "itaskdbtoolplugin.h"

class TreeDataManagerPlugin : public QObject, ITreeDataManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TreeDataManagerPlugin" FILE "PluginMeta.json")
    Q_INTERFACES(IDataManagerPlugin ITreeDataManagerPlugin)

public:
    TreeDataManagerPlugin();
    ~TreeDataManagerPlugin();

    bool SetDataSource(QObject *dataSource) override;
    QString GetError() override;

    QList<TreeItemInfo> GetTreeData(QString treeName) override;
    QMap<QString, QVariant::Type> GetTreeHeader(QString treeName) override;

    bool SetRelation(QString mainName, QString relationName, QMap<QString, QVariant::Type> fields) override;
    bool DeleteRelation(QString mainName, QString relationName) override;

    int AddItem(QString treeName, TreeItemInfo item) override;
    bool EditItem(QString treeName, TreeItemInfo item) override;
    bool DeleteItem(QString treeName, int id) override;

private:
    bool IsTableExists(QString tableName);
    bool IsTableRightStructure(QString tableName);
    QString GetCoreTableStructString();
    QString GetTableStructString(QMap<QString, QVariant::Type> tableStruct);

    IDataBaseSourcePlugin* dataSource;

    QMap<QString, QVariant::Type> coreTableStruct;

    QMap<QString, QList<QString>> relationsMap;
    QMap<QString, QMap<QString, QVariant::Type>> relationsDataMap;

};

#endif // TASKDBTOOLPLUGIN_H
