#ifndef TASKSKETCHMODEL_H
#define TASKSKETCHMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/itasksketchmodel.h"
#include "../../Interfaces/iextendabledatamanager.h"
#include "../../Interfaces/itasktreemodel.h"

//! \addtogroup TaskSketchModel_imp
//! \{
class TaskSketchModel : public PluginBase, ITaskSketchModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin ITaskSketchModel)

public:
    TaskSketchModel();
    virtual ~TaskSketchModel() override;

private:
    Q_PROPERTY(IExtendableDataManager* dataManager MEMBER dataManager)
    IExtendableDataManager *dataManager;
    ITaskTreeModel *myModel;
    QAbstractItemModel *taskModel;
    QAbstractItemModel *sketchItemModel;

    QString tableName;
    QString coreRelationName;

    // ITaskSketchModel interface
public:
    QAbstractItemModel *GetModel() override;
    QAbstractItemModel *GetInternalModel() override;
    void ConvertSketchToTask(int sketchId) override;
    void LinkEditorWidget(QWidget *widget) override;

    // PluginBase interface
protected:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;
};
//! \}
#endif // TASKLISTMODEL_H
