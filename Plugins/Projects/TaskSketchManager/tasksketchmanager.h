#ifndef TaskSketchManager_H
#define TaskSketchManager_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/itasksketchmanager.h"
#include "../../Interfaces/iextendabledatamanager.h"
#include "../../Interfaces/iusertaskmanager.h"

//! \addtogroup TaskSketchManager_imp
//! \{
class TaskSketchManager : public PluginBase, ITaskSketchManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin ITaskSketchManager)

public:
    TaskSketchManager();
    virtual ~TaskSketchManager() override;

private:
    Q_PROPERTY(IExtendableDataManager* dataManager MEMBER dataManager)
    IExtendableDataManager *dataManager;
    IUserTaskManager *myModel;
    QAbstractItemModel *taskModel;
    QAbstractItemModel *sketchItemModel;

    QString tableName;
    QString coreRelationName;

    // ITaskSketchManager interface
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
