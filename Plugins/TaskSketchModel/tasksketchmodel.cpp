#include "tasksketchmodel.h"

TaskSketchModel::TaskSketchModel()
{
    tableName = "sketch";
    coreRelationName = "image";
    activeViewId = -1;
    myModel = NULL;
    dataManager = NULL;
}

TaskSketchModel::~TaskSketchModel()
{
}

void TaskSketchModel::OnAllSetup()
{
    if(dataManager == NULL) return;
    QMap<QString, QVariant::Type> newRelationStruct = {
        {coreRelationName,  QVariant::ByteArray},
    };
    QVector<QVariant> defaultData;
    defaultData << QByteArray();
    dataManager->SetRelation(tableName, coreRelationName, newRelationStruct, defaultData);
    if(myModel != NULL)
        dataManager->SetRelation(myModel->GetDataName(), coreRelationName, newRelationStruct, defaultData);
}

QString TaskSketchModel::GetLastError()
{
    return "";
}

void TaskSketchModel::AddDataManager(QObject *DBTool)
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

void TaskSketchModel::AddModel(QObject *instance, MetaInfo *meta)
{
    myModel = qobject_cast<ITaskTreeModel*>(instance);
    if(!myModel){
        qDebug() << instance->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
    connect(this, SIGNAL(OnClose(IModelPlugin*)), instance, SLOT(RelatedModelClosed(IModelPlugin*)));
}

void TaskSketchModel::AddView(QObject *instance, MetaInfo *meta)
{
    IViewPlugin *view = qobject_cast<IViewPlugin*>(instance);
    PluginInfo<IViewPlugin> newPlugin = {view, meta};
    viewPlugins.append(newPlugin);
    qDebug() << "IPluginView succesfully set.";
    connect(instance, SIGNAL(OnClose(IViewPlugin*)), SLOT(RelatedViewClosed(IViewPlugin*)));
}

bool TaskSketchModel::Open(IModelPlugin *parent, QWidget *parentWidget)
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

void TaskSketchModel::RelatedModelClosed(IModelPlugin *model)
{
    Close();
}

void TaskSketchModel::RelatedViewClosed(IViewPlugin *view)
{
    Close();
}

void TaskSketchModel::Close()
{
    activeViewId = -1;
    emit OnClose(this);
    emit OnClose();
}

QAbstractItemModel *TaskSketchModel::GetModel()
{
    return taskModel;
}

QAbstractItemModel *TaskSketchModel::GetInternalModel()
{
    return sketchItemModel;
}

void TaskSketchModel::ConvertSketchToTask(int sketchId)
{
    QModelIndex modelIndex;
    QMap<int, QVariant> map;

    modelIndex = sketchItemModel->index(sketchId, 0);
    map = sketchItemModel->itemData(modelIndex);
    qDebug() << map[0];

    taskModel->insertRows(taskModel->rowCount(), 1);
    modelIndex = taskModel->index(taskModel->rowCount()-1, 0);
    dataManager->SetActiveRelation(myModel->GetDataName(), coreRelationName);
    taskModel->setData(modelIndex, map[1]);
    qDebug() << map[0];

    //emit ConvertTaskToSketch(map[0].toInt());
}

void TaskSketchModel::SetupModel()
{
    taskModel = dataManager->GetDataModel(myModel->GetDataName());
    sketchItemModel = dataManager->GetDataModel(tableName);
}
