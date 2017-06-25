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
    void OnAllSetup() override;
    QString GetLastError() override;

    // IModelPlugin interface
public:
    void AddDataManager(QObject *dataManager) override;
    void AddModel(QObject *model, MetaInfo *meta) override;
    void AddView(QObject *view, MetaInfo *meta) override;
public slots:
    bool Open(IModelPlugin *model, QWidget *modelWidget) override;
    void Close() override;
signals:
    void OnClose(IModelPlugin *model);
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

    template <class T>
    struct PluginInfo
    {
        T *plugin;
        MetaInfo *meta;
    };

    QList< PluginInfo<IModelPlugin> > childModelPlugins;
    QList< PluginInfo<IViewPlugin> > viewPlugins;

    // Unique part
    QString tableName;
    QString relationName;
    IExtendableDataBaseManagerPlugin* dataManager;
    QAbstractItemModel *treeModel;

    QMap<QString, ITaskRelationDelegate*> taskRelationDelegates;
};
//! \}
#endif // TASKLISTMODEL_H
