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

void TaskSketchModel::AddChildModel(IModelPlugin *plugin, MetaInfo *meta)
{
    qDebug() << "New child" << meta->Name;
    PluginInfo<IModelPlugin> newPlugin = {plugin, meta};
    childModelPlugins.append(newPlugin);
}

void TaskSketchModel::AddView(IViewPlugin *view, MetaInfo *meta)
{
    PluginInfo<IViewPlugin> newPlugin = {view, meta};
    viewPlugins.append(newPlugin);
    qDebug() << "IPluginView succesfully set.";
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

void TaskSketchModel::AddModel(QObject *model, MetaInfo *meta)
{
    myModel = qobject_cast<ITaskTreeModel*>(model);
    if(!myModel){
        qDebug() << model->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
    connect(this, SIGNAL(ConvertTaskToSketch(int)), model, SIGNAL(OpenTaskEdit(int)));
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
    if(!viewPlugins[activeViewId].plugin->Open(myParentWidget)){
        qDebug() << "Can't open first view!";
        return false;
    }
    return true;
}

bool TaskSketchModel::CloseFromView(IViewPlugin *view)
{
    myModel->ChildSelfClosed(this);
    activeViewId = -1;
    return true;
}

void TaskSketchModel::ChildSelfClosed(IModelPlugin *child)
{

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
