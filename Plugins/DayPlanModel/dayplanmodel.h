#ifndef DAYPLANMODEL_H
#define DAYPLANMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>
#include <QDateTime>

#include "idayplanmodel.h"
#include "../TaskListModel/itasktreemodel.h"
#include "../ExtendableDataManager/iextendabledatamanager.h"

//! addtogroup DayPlanModel_imp
//! {
class DayPlanModel : public QObject, IDayPlanModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IModelPlugin
            IDayPlanModel
            )

public:
    DayPlanModel();
    ~DayPlanModel();

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

signals:
    void OnClose(PluginInfo*);
    void OnClose();

    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    void Close() override;


private:
    PluginInfo *pluginInfo;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

private:
    ITaskTreeModel *taskTreeModel;
    IExtendableDataManager *dataManager;
    QString tableName, relationName;
    QAbstractItemModel *dataModel;

    // IDayPlanModel interface
public:
    QAbstractItemModel *GetModel() override;
};
//! }
#endif // DAYPLANMODEL_H
