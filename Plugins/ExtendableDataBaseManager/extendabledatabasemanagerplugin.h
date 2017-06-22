#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include <QHash>
#include <QString>
#include <QObject>
#include <QVariant>

#include "iextendabledatabasemanagerplugin.h"
#include "tablehandler.h"
#include "extendableitemmodel.h"

//! \addtogroup ExtendableDataBaseManagerPlugin_imp
//! \{
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

    QList<ManagerDataItem> GetDataList(QString tableName) override;
    ManagerDataItem GetDataItem(QString tableName, int id) override;
    QAbstractItemModel *GetDataModel(QString tableName) override;
    QMap<QString, QVariant::Type> GetTableHeader(QString tableName) override;

    bool SetRelation(QString tableName, QString relationName, QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData) override;
    bool DeleteRelation(QString tableName, QString relationName) override;
    bool SetActiveRelation(QString tableName, QString relationName) override;

    int AddItem(QString tableName, ManagerDataItem item) override;
    bool EditItem(QString tableName, ManagerDataItem item) override;
    bool DeleteItem(QString tableName, int id) override;

private:
    QString lastError;
    IDataBaseSourcePlugin* dataSource;

    QHash<QString, TableHandler*> tableHandlers;

};
//! \}
#endif // TASKDBTOOLPLUGIN_H
