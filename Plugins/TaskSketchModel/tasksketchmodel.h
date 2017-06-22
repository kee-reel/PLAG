#ifndef TASKSKETCHMODEL_H
#define TASKSKETCHMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>

#include "itasksketchmodel.h"
#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"
#include "../TaskListModel/itasktreemodel.h"

//! \addtogroup TaskSketchModel_imp
//! \{
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
    IExtendableDataBaseManagerPlugin *dataManager;
    ITaskTreeModel *myModel;
    QAbstractItemModel *taskModel;
    QAbstractItemModel *sketchItemModel;
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
    QString coreRelationName;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IPluginModel interface
public:
    void AddDataManager(QObject *) override;
    void AddParentModel(QObject *model, MetaInfo *meta) override;
    void AddChildModel(IModelPlugin *, MetaInfo *) override; 
    void AddView(IViewPlugin *view, MetaInfo *meta) override;
    bool Open(IModelPlugin *parent, QWidget *parentWidget) override;
    bool CloseFromView(IViewPlugin *view) override;
    void ChildSelfClosed(IModelPlugin *child) override;

    // ITaskSketchModel interface
public:
    QAbstractItemModel *GetModel() override;
    QAbstractItemModel *GetInternalModel() override;
    void ConvertSketchToTask(int sketchId) override;

private:
    void SetupModel();

};
//! \}
#endif // TASKLISTMODEL_H
