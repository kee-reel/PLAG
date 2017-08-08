#include "pomodoromodel.h"

PomodoroModel::PomodoroModel()
{
    myModel = NULL;
    dataManager = NULL;
    tableName = "pomodoro";
    coreRelationName = "project";
    activeViewId = -1;
    finishedPomodoros = 0;
}

PomodoroModel::~PomodoroModel()
{
}

void PomodoroModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void PomodoroModel::OnAllSetup()
{
    if(!dataManager) return;
    QMap<QString, QVariant::Type> newRelationStruct = {
        {coreRelationName,  QVariant::String},
        {"pomodoros",       QVariant::Int},
    };
    QVector<QVariant> defaultData;
    defaultData << "Sample project" << 0;
    dataManager->SetRelation(tableName, coreRelationName, newRelationStruct, defaultData);
//    if(!myModel) return;
//    dataManager->SetRelation(myModel->GetDataName(), coreRelationName, newRelationStruct, defaultData);
}

QString PomodoroModel::GetLastError()
{

}

void PomodoroModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
        case PLUGINVIEW:{
            viewPlugins.append(pluginInfo);
            qDebug() << "IPluginView succesfully set.";
            connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
        } break;

        case PLUGINMODEL:{
            if(!pluginInfo->Meta->InterfaceName.compare("ITaskTreeModel", Qt::CaseInsensitive)){
                myModel = qobject_cast<ITaskTreeModel*>(pluginInfo->Instance);
                if(!myModel){
                    qDebug() << pluginInfo->Instance->objectName() << "is not ITaskTreeModel.";
                    return;
                }
                qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
                connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            }
        } break;

        case ROOTMODEL:{
            if(!pluginInfo->Meta->InterfaceName.compare("IMainMenuModel", Qt::CaseInsensitive)){
                pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
            }
        } break;

        case DATAMANAGER:{
            qDebug() <<  "is not IExtendableDataBaseManagerPlugin.";
            this->dataManager = qobject_cast<IExtendableDataBaseManager*>(pluginInfo->Instance);
            if(!this->dataManager)
            {
                qDebug() << pluginInfo->Instance->objectName() << "is not IExtendableDataBaseManagerPlugin.";
                return;
            }
            qDebug() << "IExtendableDataBaseManagerPlugin succesfully set.";
        }break;
    }
}

void PomodoroModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
    Close();
}

bool PomodoroModel::Open(IModelPlugin *parent, QWidget *parentWidget)
{
    qDebug() << "PomodoroModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }
    myParentWidget = parentWidget;
    activeViewId = 0;
    SetupModel();
    qDebug() << viewPlugins[activeViewId]->Meta->Name;
    if(!viewPlugins[activeViewId]->Plugin.view->Open(this, myParentWidget)){
        qDebug() << "Can't open first view!";
        return false;
    }
    return true;
}

void PomodoroModel::Close()
{
    activeViewId = -1;
    emit OnClose(pluginInfo);
    emit OnClose();
}

QAbstractItemModel *PomodoroModel::GetModel()
{
    return taskModel;
}

QAbstractItemModel *PomodoroModel::GetInternalModel()
{
    return pomodoroItemModel;
}

void PomodoroModel::SetupModel()
{
    if(!dataManager) return;
    pomodoroItemModel = dataManager->GetDataModel(tableName);
//    if(!myModel) return;
//    taskModel = dataManager->GetDataModel(myModel->GetDataName());
}
