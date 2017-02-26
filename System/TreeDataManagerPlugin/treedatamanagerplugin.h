#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include <QString>
#include <QtSql>
#include <QObject>

#include "itreedatamanagerplugin.h"

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
    QVector<TableStructItem> GetTreeHeader(QString treeName) override;

    bool SetRelation(QString mainName, QString relationName, QVector<TableStructItem> fields) override;
    bool DeleteRelation(QString mainName, QString relationName) override;

    int AddItem(QString treeName, TreeItemInfo item) override;
    bool EditItem(QString treeName, TreeItemInfo item) override;
    bool DeleteItem(QString treeName, int id) override;

private:
    bool IsTableExists(QString tableName);
    bool IsTableRightStructure(QString tableName);
    QString GetTableStructString(QVector<TableStructItem> &tableStruct);
    QList<TreeItemInfo> GetDataFromTableGroup(QString &treeName);

    IDataBaseSourcePlugin* dataSource;

    QVector<TableStructItem> coreTableStruct;
    QVector<TableStructItem> wholeTableStruct;

    QMap<QString, QList<QString>> relationsMap;
    QMap<QString, QVector<TableStructItem>> relationsTableStruct;
};

#endif // TASKDBTOOLPLUGIN_H
