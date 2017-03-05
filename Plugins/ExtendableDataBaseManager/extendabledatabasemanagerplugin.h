#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include <QHash>
#include <QString>
#include <QObject>
#include <QVariant>


#include "iextendabledatabasemanagerplugin.h"
#include "tablehandler.h"

class ExtendableDataBaseManagerPlugin : public QObject, IExtendableDataBaseManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TreeDataManagerPlugin" FILE "PluginMeta.json")
    Q_INTERFACES(IDataManagerPlugin IExtendableDataBaseManagerPlugin)

public:
    ExtendableDataBaseManagerPlugin();
    ~ExtendableDataBaseManagerPlugin();
    virtual void OnAllSetup();
    virtual QString GetLastError();

    bool SetDataSource(QObject *dataSource) override;

    QList<ManagerItemInfo> GetData(QString tableName) override;
    QMap<QString, QVariant::Type> GetTreeHeader(QString tableName) override;

    bool SetRelation(QString tableName, QString relationName, QMap<QString, QVariant::Type> fields) override;
    bool DeleteRelation(QString tableName, QString relationName) override;
    int AddItem(QString tableName, ManagerItemInfo item) override;
    bool EditItem(QString tableName, ManagerItemInfo item) override;
    bool DeleteItem(QString tableName, int id) override;

private:
    QString lastError;
    IDataBaseSourcePlugin* dataSource;

    QHash<QString, TableHandler*> tableHandlers;
};

#endif // TASKDBTOOLPLUGIN_H
