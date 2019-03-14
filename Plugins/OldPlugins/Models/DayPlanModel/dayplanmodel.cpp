#include "dayplanmodel.h"

DayPlanModel::DayPlanModel()
{
    openedView = nullptr;
    openedModel = nullptr;
    taskTreeModel = nullptr;
    taskDataModel = nullptr;
    dateDataModel = nullptr;
    dataManager = nullptr;
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
    dataManager->AddExtention(tableName, relationName, newRelationStruct, defaultData);
    dataManager->AddExtention(relationName, relationName, newRelationStruct, defaultData);
}

QString DayPlanModel::GetLastError()
{

}

void DayPlanModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
    case VIEWPLUGIN:{
        relatedViewPlugins.append(pluginInfo);
        qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
    } break;

    case MODELPLUGIN:{
        relatedModelPlugins.append(pluginInfo);
        qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));

        if(taskTreeModel = qobject_cast<ITaskTreeModel*>(pluginInfo->Instance))
        {
            qDebug() << "ITaskTreeModel Binded";
        }
    } break;

    case COREPLUGIN:{
        pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
    } break;

    case DATAMANAGERPLUGIN:{
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
        openedView = nullptr;
        return false;
    }

    if(dataManager != nullptr)
    {
        dataManager->SetActiveExtention(tableName, relationName);
    }

    return true;
}

void DayPlanModel::Close()
{
    qDebug() << "DayPlanModel close.";
    if(openedView != nullptr && !openedView->Plugin.view->Close()){
        qDebug() << "View plugin" << openedView->Meta->Name
                 << "not closed, but model closing anyway.";
    }
    if(openedModel != nullptr)
        openedView->Plugin.view->Close();

    openedView = nullptr;
    openedModel = nullptr;
    emit OnClose(pluginInfo);
    emit OnClose();
}

QAbstractItemModel *DayPlanModel::GetTaskModel()
{
    if(!dataManager) return nullptr;
    if(!taskDataModel) taskDataModel = dataManager->GetDataModel(tableName);
    return taskDataModel;
}

QAbstractItemModel *DayPlanModel::GetDateModel()
{
    if(!dataManager) return nullptr;
    if(!dateDataModel) dateDataModel = dataManager->GetDataModel(relationName);
    return dateDataModel;
}

void DayPlanModel::SetDataTypeEditor(QWidget *widget)
{
    if(dataManager)
        dataManager->RegisterExtentionFieldEditor(relationName, "datetime", widget);
}
