#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include <QHash>
#include <QString>
#include <QWidget>
#include <QVariant>
#include <QPair>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/iextendabledatamanager.h"
#include "../../Interfaces/idatabase.h"

#include "tablehandler.h"
#include "extendableitemmodel.h"

//! \addtogroup ExtendableDataManager_imp
//!  \{
class ExtendableDataManager : public PluginBase, IExtendableDataManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ExtendableDataManager" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IExtendableDataManager
    )

public:
    ExtendableDataManager();
    virtual ~ExtendableDataManager() override;


    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;

    // IExtendableDataManagerPlugin interface
public:
    bool RegisterExtentionFieldEditor(QString relation, QString field, QWidget *widget) override;
    QWidget *GetExtentionFieldEditor(QString relation, QString field) override;
    QList<ManagerDataItem> GetDataList(QString treeName) override;
    ManagerDataItem GetDataItem(QString treeName, int id) override;
    QAbstractItemModel *GetDataModel(QString treeName) override;
    QAbstractItemModel *GetDataModel(QVector<QPair<QString, QString> > dataModelFields) override;
    QMap<QString, QVariant::Type> GetTableHeader(QString treeName) override;
    bool AddExtention(QString mainName, QString extentionName, QMap<QString, QVariant::Type> fields, QVector<QVariant> defaultData) override;
    bool DeleteExtention(QString mainName, QString extentionName) override;
    bool SetActiveExtention(QString mainName, QString extentionName) override;
    int AddItem(QString treeName, ManagerDataItem task) override;
    bool UpdateItem(QString treeName, ManagerDataItem task) override;
    bool DeleteItem(QString treeName, int id) override;

    void SetupDataTypeEditors(QString tableName);

private:
    QString lastError;
    IDataBase* dataSource;

    QMap<QString, QMap<QString, QWidget*> > dataTypeEditorsMap;

    QHash<QString, TableHandler*> tableHandlers;
    void SetupTable(QString &tableName);
    QAbstractItemModel *CreateProxy(QVector<QPair<QString, QString> > &dataModelFields);
};
//!  \}
#endif // TASKDBTOOLPLUGIN_H
