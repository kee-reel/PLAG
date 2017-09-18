#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include <QHash>
#include <QString>
#include <QObject>
#include <QVariant>

#include "iextendabledatamanager.h"
#include "tablehandler.h"
#include "extendableitemmodel.h"

//! \addtogroup ExtendableDataBaseManagerPlugin_imp
//! \{
class ExtendableDataBaseManagerPlugin : public QObject, IExtendableDataManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ExtendableDataManager" FILE "PluginMeta.json")
    Q_INTERFACES(IDataManagerPlugin IExtendableDataManager)

public:
    ExtendableDataBaseManagerPlugin();
    ~ExtendableDataBaseManagerPlugin();

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;
public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;
signals:
    void OnClose(PluginInfo *pointer);
    void OnClose();

    // IExtendableDataManagerPlugin interface
public:
    QList<ManagerDataItem> GetDataList(QString treeName) override;
    ManagerDataItem GetDataItem(QString treeName, int id) override;
    QAbstractItemModel *GetDataModel(QString treeName) override;
    QMap<QString, QVariant::Type> GetTableHeader(QString treeName) override;
    bool SetRelation(QString mainName, QString relationName, QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData) override;
    bool DeleteRelation(QString mainName, QString relationName) override;
    bool SetActiveRelation(QString mainName, QString relationName) override;
    int AddItem(QString treeName, ManagerDataItem task) override;
    bool UpdateItem(QString treeName, ManagerDataItem task) override;
    bool DeleteItem(QString treeName, int id) override;
    //bool AddDataSource(QObject *dataSource) override;

private:
    QString lastError;
    IDataBaseSourcePlugin* dataSource;

    QHash<QString, TableHandler*> tableHandlers;
    void SetupTable(QString &tableName);
};
//! \}
#endif // TASKDBTOOLPLUGIN_H
