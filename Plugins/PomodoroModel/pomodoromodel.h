#ifndef TASKSKETCHMODEL_H
#define TASKSKETCHMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>
#include <QDateTime>

#include "ipomodoromodel.h"
#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"
#include "../TaskListModel/itasktreemodel.h"

//! \addtogroup PomodoroModel_imp
//! \{
class PomodoroModel : public QObject, IPomodoroModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin IPomodoroModel)

public:
    PomodoroModel();
    ~PomodoroModel();

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

    // IModelPlugin interface
public:
    void AddDataManager(QObject *dataManager) override;
    void AddModel(QObject *instance, MetaInfo *meta) override;
    void AddView(QObject *instance, MetaInfo *meta) override;
public slots:
    bool Open(IModelPlugin *model, QWidget *modelWidget) override;
    void RelatedModelClosed(IModelPlugin *model) override;
    void RelatedViewClosed(IViewPlugin *view) override;
    void Close() override;
signals:
    void OnClose(IModelPlugin *pointer);
    void OnClose();

    // IPomodoroModel interface
public:
    QAbstractItemModel *GetModel() override;
    QAbstractItemModel *GetInternalModel() override;

private:
    void SetupModel();

};
//! \}
#endif // TASKLISTMODEL_H
