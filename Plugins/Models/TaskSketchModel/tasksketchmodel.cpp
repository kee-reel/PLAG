#include "tasksketchmodel.h"

TaskSketchModel::TaskSketchModel()
{
    tableName = "itasksketchmodel";
    coreRelationName = "itasksketchmodel";
    activeViewId = -1;
    myModel = nullptr;
    dataManager = nullptr;
}

TaskSketchModel::~TaskSketchModel()
{
}

void TaskSketchModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void TaskSketchModel::OnAllSetup()
{
    if(dataManager == nullptr)
        return;

    QMap<QString, QVariant::Type> newRelationStruct =
    {
        {"sketch",  QVariant::ByteArray},
    };
    QVector<QVariant> defaultData;
    defaultData << QByteArray();
    dataManager->AddExtention(tableName, coreRelationName, newRelationStruct, defaultData);

    if(myModel != nullptr)
        dataManager->AddExtention("ITaskTreeModel", coreRelationName, newRelationStruct, defaultData);
}

QString TaskSketchModel::GetLastError()
{
    return "";
}

void TaskSketchModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
        case VIEWPLUGIN:
        {
            viewPlugins.append(pluginInfo);
            qDebug() << "IPluginView succesfully set.";
            connect(pluginInfo->Instance, SIGNAL(OnClose(PluginInfo*)), SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;

        case DATAMANAGERPLUGIN:
        {
            this->dataManager = qobject_cast<IExtendableDataManager*>(pluginInfo->Instance);

            if(!this->dataManager)
            {
                qDebug() << pluginInfo->Meta->Name << "is not IExtendableDataManagerPlugin.";
                return;
            }

            qDebug() << "IExtendableDataManagerPlugin succesfully set.";
        } break;

        case MODELPLUGIN:
        {
            myModel = qobject_cast<ITaskTreeModel*>(pluginInfo->Instance);

            if(!myModel)
            {
                qDebug() << pluginInfo->Meta->Name << "is not IExtendableDataManagerPlugin.";
                return;
            }

            qDebug() << "IExtendableDataManagerPlugin succesfully set.";
        } break;

        case COREPLUGIN:
        {
            pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
        } break;
    }
}

void TaskSketchModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
    Close();
}

bool TaskSketchModel::Open(IModelPlugin *parent)
{
    qDebug() << "TaskListModel runs";

    if(viewPlugins.count() == 0)
    {
        qDebug() << "I dont have any views!";
        return false;
    }

    activeViewId = 0;
    SetupModel();
    qDebug() << viewPlugins[activeViewId]->Meta->Name;

    if(!viewPlugins[activeViewId]->Plugin.view->Open(this))
    {
        qDebug() << "Can't open first view!";
        return false;
    }

    return true;
}

void TaskSketchModel::Close()
{
    activeViewId = -1;
    emit OnClose(pluginInfo);
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
    QModelIndex modelIndex = sketchItemModel->index(sketchId, 0);
    QMap<int, QVariant> map = sketchItemModel->itemData(modelIndex);

    if(!map.contains(Qt::UserRole))
    {
        qCritical() << "Can't resolve data model!";
        return;
    }

    //    QMap<QString, QVariant> dataMap = map[Qt::UserRole].toMap();
    //    QList<QVariant> data = dataMap[coreRelationName].toList();
    taskModel->insertRows(taskModel->rowCount(), 1);
    modelIndex = taskModel->index(taskModel->rowCount()-1, 0);
    //    dataManager->SetActiveRelation(tableName, coreRelationName);
    taskModel->setItemData(modelIndex, map);
    //emit ConvertTaskToSketch(map[0].toInt());
}

void TaskSketchModel::LinkEditorWidget(QWidget *widget)
{
    if(!dataManager)
        return;

    dataManager->RegisterExtentionFieldEditor(tableName, "sketch", widget);
}

void TaskSketchModel::SetupModel()
{
    if(!dataManager)
        return;

    sketchItemModel = dataManager->GetDataModel(tableName);

    if(!myModel)
        return;

    taskModel = dataManager->GetDataModel("ITaskTreeModel");
}
