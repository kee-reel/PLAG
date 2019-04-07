#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/iusertaskmanager.h"
#include "../../Interfaces/iextendabledatamanager.h"

//! \addtogroup UserTaskManager_imp
//! \{
class UserTaskManager : public PluginBase, IUserTaskManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IUserTaskManager
    )

public:
    UserTaskManager();
    ~UserTaskManager();

    // PluginBase interface
protected:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

    // IUserTaskManager interface
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
