#ifndef DAYPLANMODEL_H
#define DAYPLANMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>
#include <QDateTime>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/idayplanmodel.h"
#include "../../Interfaces/itasktreemodel.h"
#include "../../Interfaces/iextendabledatamanager.h"

//! addtogroup DayPlanModel_imp
//! {
class DayPlanModel : public PluginBase, IDayPlanModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IDayPlanModel
    )

public:
    DayPlanModel();
    virtual ~DayPlanModel() override;

    // IPlugin interface
public:
    virtual bool open() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

private:
    ITaskTreeModel *taskTreeModel;
    IExtendableDataManager *dataManager;
    QString tableName, relationName;
    QAbstractItemModel *taskDataModel;
    QAbstractItemModel *dateDataModel;

    // IDayPlanModel interface
public:
    QAbstractItemModel *GetTaskModel() override;
    QAbstractItemModel *GetDateModel() override;
    void SetDataTypeEditor(QWidget *widget) override;
};
//! }
#endif // DAYPLANMODEL_H
