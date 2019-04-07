#include "tasksketchmanager.h"

TaskSketchManager::TaskSketchManager() :
    PluginBase()
{
    tableName = "iTaskSketchManager";
    coreRelationName = "iTaskSketchManager";
    myModel = nullptr;
    dataManager = nullptr;
}

TaskSketchManager::~TaskSketchManager()
{
}

QAbstractItemModel *TaskSketchManager::GetModel()
{
    return taskModel;
}

QAbstractItemModel *TaskSketchManager::GetInternalModel()
{
    return sketchItemModel;
}

void TaskSketchManager::ConvertSketchToTask(int sketchId)
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

void TaskSketchManager::LinkEditorWidget(QWidget *widget)
{
    dataManager->RegisterExtentionFieldEditor(tableName, "sketch", widget);
}

void TaskSketchManager::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IExtendableDataManager", Qt::CaseInsensitive))
        {
            dataManager = castPluginToInterface<IExtendableDataManager>(plugin);
        }
        else if(!QString::compare(interfaceName, "IUserTaskManager", Qt::CaseInsensitive))
        {
            myModel = castPluginToInterface<IUserTaskManager>(plugin);
        }
    }
    PluginBase::onAllReferencesSet();
}

void TaskSketchManager::onAllReferencesReady()
{
    QMap<QString, QVariant::Type> newRelationStruct =
    {
        {"sketch",  QVariant::ByteArray},
    };
    QVector<QVariant> defaultData;
    defaultData << QByteArray();
    dataManager->AddExtention(tableName, coreRelationName, newRelationStruct, defaultData);
    dataManager->AddExtention("IUserTaskManager", coreRelationName, newRelationStruct, defaultData);

    sketchItemModel = dataManager->GetDataModel(tableName);
    taskModel = dataManager->GetDataModel("IUserTaskManager");

    PluginBase::onAllReferencesReady();
}
