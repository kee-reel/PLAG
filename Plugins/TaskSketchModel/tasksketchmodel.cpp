#include "tasksketchmodel.h"

TaskSketchModel::TaskSketchModel()
{
    tableName = "sketch";
    activeViewId = -1;
}

TaskSketchModel::~TaskSketchModel()
{
}

void TaskSketchModel::OnAllSetup()
{

}

QString TaskSketchModel::GetLastError()
{

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
//    this->dataManager = qobject_cast<IExtendableDataBaseManagerPlugin*>(DBTool);
//    if(!this->dataManager)
//    {
//        qDebug() << DBTool->objectName() << "is not IExtendableDataBaseManagerPlugin.";
//        return;
//    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";\
}

void TaskSketchModel::AddParentModel(QObject *model, MetaInfo *meta)
{
    taskTreeModel = qobject_cast<ITaskTreeModel*>(model);
    if(!taskTreeModel)
    {
        qDebug() << model->objectName() << "is not IExtendableDataBaseManagerPlugin.";
        return;
    }
    qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";

    QMap<QString, QVariant::Type> newRelationStruct = {
        {"pixmap",        QVariant::ByteArray},
    };
    QVector<QVariant> defaultData;
    defaultData << QByteArray();
    taskTreeModel->AttachRelation(newRelationStruct, tableName, defaultData);
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
    taskTreeModel->SetActiveRelation(tableName);
    qDebug() << viewPlugins[activeViewId].meta->Name;
    if(!viewPlugins[activeViewId].plugin->Open(myParentWidget))
    {
        qDebug() << "Can't open first view!";
        return false;
    }
    return true;
}

bool TaskSketchModel::CloseFromView(IViewPlugin *view)
{
    taskTreeModel->ChildSelfClosed(this);
    activeViewId = -1;
    return true;
}

void TaskSketchModel::ChildSelfClosed(IModelPlugin *child)
{

}

QAbstractItemModel *TaskSketchModel::GetModel()
{
    return taskTreeModel->GetTreeModel();
}
