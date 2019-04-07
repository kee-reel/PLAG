#ifndef DayPlan_H
#define DayPlan_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>
#include <QDateTime>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/idayplan.h"
#include "../../Interfaces/iusertaskmanager.h"
#include "../../Interfaces/iextendabledatamanager.h"

//! \addtogroup DayPlan_imp
//! \{
class DayPlan : public PluginBase, IDayPlan
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IDayPlan
    )

public:
    DayPlan();
    virtual ~DayPlan() override;

    // IPlugin interface
public:
    virtual bool open() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

private:
    IUserTaskManager *taskTreeModel;
    IExtendableDataManager *dataManager;
    QString tableName, relationName;
    QAbstractItemModel *taskDataModel;
    QAbstractItemModel *dateDataModel;

    // IDayPlan interface
public:
    QAbstractItemModel *GetTaskModel() override;
    QAbstractItemModel *GetDateModel() override;
    void SetDataTypeEditor(QWidget *widget) override;
};
//! \}
#endif // DayPlan_H
