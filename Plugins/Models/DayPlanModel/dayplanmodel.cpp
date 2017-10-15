#include "dayplanmodel.h"

DayPlanModel::DayPlanModel()
{
    openedView = NULL;
    openedModel = NULL;
    taskTreeModel = NULL;
    taskDataModel = NULL;
    dateDataModel = NULL;
    dataManager = NULL;
    tableName = "ITaskTreeModel";
    relationName = "IDayPlanModel";
}

DayPlanModel::~DayPlanModel()
{
}

void DayPlanModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void DayPlanModel::OnAllSetup()
{
    if(!dataManager) return;
    QMap<QString, QVariant::Type> newRelationStruct = {
        {"datetime",        QVariant::String},
    };
    QVector<QVariant> defaultData;
    defaultData << QDateTime::currentDateTime().toString(Qt::ISODate);
    dataManager->SetRelation(tableName, relationName, newRelationStruct, defaultData);
    dataManager->SetRelation(relationName, relationName, newRelationStruct, defaultData);
}

QString DayPlanModel::GetLastError()
{

}

void DayPlanModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
    case PLUGINVIEW:{
        relatedViewPlugins.append(pluginInfo);
        qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
    } break;

    case PLUGINMODEL:{
        relatedModelPlugins.append(pluginInfo);
        qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));

        if(taskTreeModel = qobject_cast<ITaskTreeModel*>(pluginInfo->Instance))
        {
            qDebug() << "ITaskTreeModel Binded";
        }
    } break;

    case ROOTMODEL:{
        pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
    } break;

    case DATAMANAGER:{
        dataManager = qobject_cast<IExtendableDataManager*>(pluginInfo->Instance);
        if(!this->dataManager){
            qDebug() << pluginInfo->Meta->Name << "is not IExtendableDataManager.";
            return;
        }
    }break;
    }
}

void DayPlanModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool DayPlanModel::Open(IModelPlugin *parent)
{
    qDebug() << "DayPlanModel open.";
    if(relatedViewPlugins.count() == 0){
        qDebug() << "!DayPlanModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "DayPlanModel opens related view " << openedView->Meta->Name;
    if(!openedView->Plugin.view->Open(this)){
        qDebug() << "!Can't open first view!";
        openedView = NULL;
        return false;
    }

    if(dataManager != NULL)
    {
        dataManager->SetActiveRelation(tableName, relationName);
    }

    return true;
}

void DayPlanModel::Close()
{
    qDebug() << "DayPlanModel close.";
    if(openedView != NULL && !openedView->Plugin.view->Close()){
        qDebug() << "View plugin" << openedView->Meta->Name
                 << "not closed, but model closing anyway.";
    }
    if(openedModel != NULL)
        openedView->Plugin.view->Close();

    openedView = NULL;
    openedModel = NULL;
    emit OnClose(pluginInfo);
    emit OnClose();
}

QAbstractItemModel *DayPlanModel::GetTaskModel()
{
    if(!dataManager) return NULL;
    if(!taskDataModel) taskDataModel = dataManager->GetDataModel(tableName);
    return taskDataModel;
}

QAbstractItemModel *DayPlanModel::GetDateModel()
{
    if(!dataManager) return NULL;
    if(!dateDataModel) dateDataModel = dataManager->GetDataModel(relationName);
    return dateDataModel;
}

void DayPlanModel::SetDataTypeEditor(QWidget *widget)
{
    if(dataManager)
        dataManager->RegisterDataTypeEditor(relationName, "datetime", widget);
}
