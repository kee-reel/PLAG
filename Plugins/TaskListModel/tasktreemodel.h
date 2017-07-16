#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "itasktreemodel.h"
#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"

//! \addtogroup TaskTreeModel_imp
//! \{
class TaskTreeModel : public QObject, ITaskTreeModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin ITaskTreeModel)

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;
public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;
    // IModelPlugin interface
public:
//    void AddDataManager(QObject *dataManager) override;
//    void AddModel(QObject *instance, MetaInfo *meta) override;
//    void AddView(QObject *instance, MetaInfo *meta) override;
public slots:
    bool Open(IModelPlugin *model, QWidget *modelWidget) override;
//    void RelatedModelClosed(IModelPlugin *model) override;
//    void RelatedViewClosed(IViewPlugin *view) override;
    void Close() override;
signals:
    void OnClose(PluginInfo *pluginInfo);
    void OnClose();

    // ITaskTreeModel interface
public:
    QString GetDataName() override;
    QAbstractItemModel *GetTreeModel() override;
    void SetRelationDelegate(QString relation, ITaskRelationDelegate *delegate) override;
    QMap<QString, ITaskRelationDelegate *> GetRelationDelegates() override;
signals:
    void OpenTaskEdit(int id);

public:
    TaskTreeModel();
    ~TaskTreeModel();

private:
    void SetupModel();

    // Native part
    IModelPlugin *myParent;
    QWidget *myParentWidget;
    IViewPlugin *activeView;
    IModelPlugin *activeModel;
    PluginInfo *pluginInfo;

    QList<PluginInfo*> childModelPlugins;
    QList<PluginInfo*> viewPlugins;

    // Unique part
    QString tableName;
    QString relationName;
    IExtendableDataBaseManagerPlugin* dataManager;
    QAbstractItemModel *treeModel;

    QMap<QString, ITaskRelationDelegate*> taskRelationDelegates;

};
//! \}
#endif // TASKLISTMODEL_H
