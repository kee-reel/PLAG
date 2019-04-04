#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>

#include "../../PluginsCommon/plugin_base.h"

#include "../../PluginsInterfaces/itasktreemodel.h"
#include "../../PluginsInterfaces/iextendabledatamanager.h"

//! \addtogroup TaskTreeModel_imp
//! \{
class TaskTreeModel : public PluginBase, ITaskTreeModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        ITaskTreeModel
    )

public:
    TaskTreeModel();
    ~TaskTreeModel();

    // PluginBase interface
protected:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

    // ITaskTreeModel interface
public:
    QAbstractItemModel *GetTreeModel();
signals:
    void OpenTaskEdit(int id);

private:
    void SetupModel();

    QString tableName;
    QString relationName;
    IExtendableDataManager* dataManager;
    QAbstractItemModel *treeModel;


    // IPlugin interface
public:
    virtual bool open() override;
};
//! \}
#endif // TASKLISTMODEL_H
