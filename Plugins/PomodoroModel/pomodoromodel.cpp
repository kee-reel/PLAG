#include "pomodoromodel.h"

PomodoroModel::PomodoroModel()
{
    tableName = "pomodoro";
    coreRelationName = "datetime";
    activeViewId = -1;
}

PomodoroModel::~PomodoroModel()
{
}

void PomodoroModel::OnAllSetup()
{
    QMap<QString, QVariant::Type> newRelationStruct = {
        {coreRelationName,  QVariant::ByteArray},
    };
    QVector<QVariant> defaultData;
    defaultData << QDateTime();
    dataManager->SetRelation(tableName, coreRelationName, newRelationStruct, defaultData);
    dataManager->SetRelation(myModel->GetDataName(), coreRelationName, newRelationStruct, defaultData);
}

QString PomodoroModel::GetLastError()
{

}

void PomodoroModel::AddChildModel(IModelPlugin *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IModelPlugin> newPlugin = {plugin, meta};
    childModelPlugins.append(newPlugin);
}

void PomodoroModel::AddView(IViewPlugin *view, MetaInfo *meta)
{
    PluginInfo<IViewPlugin> newPlugin = {view, meta};
    viewPlugins.append(newPlugin);
    qDebug() << "IPluginView succesfully set.";
}

void PomodoroModel::AddDataManager(QObject *DBTool)
{
    qDebug() <<  "is not IExtendableDataBaseManagerPlugin.";
    this->dataManager = qobject_cast<IExtendableDataBaseManagerPlugin*>(DBTool);
    if(!this->dataManager)
    {
        qDebug() << DBTool->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
}

void PomodoroModel::AddParentModel(QObject *model, MetaInfo *meta)
{
    myModel = qobject_cast<ITaskTreeModel*>(model);
    if(!myModel){
        qDebug() << model->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
}

bool PomodoroModel::Open(IModelPlugin *parent, QWidget *parentWidget)
{
    qDebug() << "TaskListModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }
    myParentWidget = parentWidget;
    activeViewId = 0;
    SetupModel();
    qDebug() << viewPlugins[activeViewId].meta->Name;
    if(!viewPlugins[activeViewId].plugin->Open(myParentWidget)){
        qDebug() << "Can't open first view!";
        return false;
    }
    return true;
}

bool PomodoroModel::CloseFromView(IViewPlugin *view)
{
    myModel->ChildSelfClosed(this);
    activeViewId = -1;
    return true;
}

void PomodoroModel::ChildSelfClosed(IModelPlugin *child)
{

}

QAbstractItemModel *PomodoroModel::GetModel()
{
    return taskModel;
}

QAbstractItemModel *PomodoroModel::GetInternalModel()
{
    return sketchItemModel;
}

void PomodoroModel::SetupModel()
{
    taskModel = dataManager->GetDataModel(myModel->GetDataName());
    sketchItemModel = dataManager->GetDataModel(tableName);
}
