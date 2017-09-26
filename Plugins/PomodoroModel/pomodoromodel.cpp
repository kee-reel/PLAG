#include "pomodoromodel.h"

PomodoroModel::PomodoroModel()
{
    myModel = NULL;
    dataManager = NULL;
    tableName = "itasktreemodel";
    coreRelationName = "ipomodoromodel";
    activeViewId = -1;
    workSetup.easyRestDuration = 5;
    workSetup.longRestDuration = 15;
    workSetup.longRestPeriod = 3;
    workSetup.workSessionDuration = 25;
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
        {"pomodoros",   QVariant::Int}
    };
    QVector<QVariant> defaultData;
    defaultData << 0;
    dataManager->SetRelation(tableName, coreRelationName, newRelationStruct, defaultData);
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
                qDebug() << "IExtendableDataManagerPlugin succesfully set.";
                connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            }
        } break;

        case ROOTMODEL:{
            if(!pluginInfo->Meta->InterfaceName.compare("IMainMenuModel", Qt::CaseInsensitive)){
                pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
            }
        } break;

        case DATAMANAGER:{
            qDebug() <<  "is not IExtendableDataManagerPlugin.";
            this->dataManager = qobject_cast<IExtendableDataManager*>(pluginInfo->Instance);
            if(!this->dataManager)
            {
                qDebug() << pluginInfo->Meta->Name << "is not IExtendableDataManagerPlugin.";
                return;
            }
            qDebug() << "IExtendableDataManagerPlugin succesfully set.";
        }break;
    }
}

void PomodoroModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{
    Close();
}

bool PomodoroModel::Open(IModelPlugin *parent)
{
    qDebug() << "PomodoroModel runs";
    if(viewPlugins.count() == 0){
        qDebug() << "I dont have any views!";
        return false;
    }
    activeViewId = 0;
    SetupModel();
    qDebug() << viewPlugins[activeViewId]->Meta->Name;
    if(!viewPlugins[activeViewId]->Plugin.view->Open(this)){
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

QAbstractItemModel *PomodoroModel::GetTaskModel()
{
    return taskModel;
}

void PomodoroModel::SetActiveProject(QModelIndex index)
{
//    currentProject = pomodoroItemModel->index(index.row(), 0);
//    finishedPomodoros = pomodoroItemModel->index(index.row(), 1);
}

QModelIndex* PomodoroModel::GetActiveProject()
{
    return &currentProject;
}

IPomodoroModel::WorkSetup PomodoroModel::GetWorkSetup()
{
    return workSetup;
}

void PomodoroModel::SetupModel()
{
    if(!dataManager) return;
    taskModel = dataManager->GetDataModel(tableName);
    dataManager->SetActiveRelation(tableName, coreRelationName);
    currentProject = taskModel->index(0,0);
    finishedPomodoros = taskModel->index(0,1);

}
