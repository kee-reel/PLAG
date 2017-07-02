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

void PomodoroModel::AddModel(QObject *instance, MetaInfo *meta)
{
    myModel = qobject_cast<ITaskTreeModel*>(instance);
    if(!myModel){
        qDebug() << instance->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
    connect(this, SIGNAL(OnClose(IModelPlugin*)), instance, SLOT(RelatedModelClosed(IModelPlugin*)));
}

void PomodoroModel::AddView(QObject *instance, MetaInfo *meta)
{
    IViewPlugin *view = qobject_cast<IViewPlugin*>(instance);
    PluginInfo<IViewPlugin> newPlugin = {view, meta};
    viewPlugins.append(newPlugin);
    qDebug() << "IPluginView succesfully set.";
    connect(instance, SIGNAL(OnClose(IViewPlugin*)), SLOT(RelatedViewClosed(IViewPlugin*)));
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
    if(!viewPlugins[activeViewId].plugin->Open(this, myParentWidget)){
        qDebug() << "Can't open first view!";
        return false;
    }
    return true;
}

void PomodoroModel::RelatedModelClosed(IModelPlugin *model)
{
    Close();
}

void PomodoroModel::RelatedViewClosed(IViewPlugin *view)
{
    Close();
}

void PomodoroModel::Close()
{
    activeViewId = -1;
    emit OnClose(this);
    emit OnClose();
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
