#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>\

#include "itasksketchmodel.h"
#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"

class TaskSketchModel : public QObject, ITaskSketchModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin ITaskSketchModel)

public:
    TaskSketchModel();
    ~TaskSketchModel();

private:
    // Native part
    IModelPlugin *myParent;
    QWidget *myParentWidget;
    int myModelId;
    int activeViewId;
    int activeModelId;

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
    IExtendableDataBaseManagerPlugin *dataManager;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IPluginModel interface
public:
    void AddChildModel(IModelPlugin *, MetaInfo *) override;
    void AddDataManager(QObject *) override;
    void AddView(IViewPlugin *view, MetaInfo *meta) override;
    bool Open(IModelPlugin *parent, QWidget *parentWidget) override;
    bool CloseFromView(IViewPlugin *view) override;
    void ChildSelfClosed(IModelPlugin *child) override;

    // ITaskSketchModel interface
public:
    virtual QAbstractItemModel *GetModel();
};

#endif // TASKLISTMODEL_H
