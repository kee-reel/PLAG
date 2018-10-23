#include "pomodoromodel.h"

PomodoroModel::PomodoroModel()
{
    myModel = nullptr;
    notificationManger = nullptr;
    dataManager = nullptr;
    tableName = "itasktreemodel";
    coreRelationName = "ipomodoromodel";
    activeViewId = -1;
    workSetup.easyRestDuration = 5 * 60;
    workSetup.longRestDuration = 15 * 60;
    workSetup.longRestPeriod = 3;
    workSetup.workSessionDuration = 35 * 60;
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
    dataManager->AddExtention(tableName, coreRelationName, newRelationStruct, defaultData);
}

QString PomodoroModel::GetLastError()
{

}

void PomodoroModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
        case VIEWPLUGIN:{
            viewPlugins.append(pluginInfo);
            qDebug() << "IPluginView succesfully set.";
            connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
        } break;

        case MODELPLUGIN:{
            if(!pluginInfo->Meta->InterfaceName.compare("ITaskTreeModel", Qt::CaseInsensitive))
            {
                myModel = qobject_cast<ITaskTreeModel*>(pluginInfo->Instance);
                if(!myModel){
                    qDebug() << pluginInfo->Instance->objectName() << "is not ITaskTreeModel.";
                    return;
                }
                connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            }
            else if(!pluginInfo->Meta->InterfaceName.compare("INotificationMangerModel", Qt::CaseInsensitive))
            {
                notificationManger = qobject_cast<INotificationManagerModel*>(pluginInfo->Instance);
                if(!notificationManger){
                    qDebug() << pluginInfo->Instance->objectName() << "is not INotificationManagerModel.";
                    return;
                }
                auto res = connect(pluginInfo->Instance, SIGNAL(OnTimerTimeout(int)), SLOT(OnTimerEnded(int)));
                qDebug() << "~CONNECTED" << res;
            }
        } break;

        case COREPLUGIN:{
            if(!pluginInfo->Meta->InterfaceName.compare("IMainMenuModel", Qt::CaseInsensitive)){
                pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
            }
        } break;

        case DATAMANAGERPLUGIN:{
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
    currentTask = index;
}

QModelIndex* PomodoroModel::GetActiveProject()
{
    return &currentTask;
}

IPomodoroModel::WorkSetup PomodoroModel::GetWorkSetup()
{
    return workSetup;
}

void PomodoroModel::StartPomodoro()
{
    notificationTimerId = notificationManger->
            SetAlarm(INotificationManagerModel::RTC_TIME,
                     QDateTime::currentDateTime().addSecs(workSetup.workSessionDuration));

    notificationManger->SetAlarmedNotification(INotificationManagerModel::RTC_TIME,
             QDateTime::currentDateTime().addSecs(workSetup.workSessionDuration),
                           "Message from Pomodoro:",
                           "You can take a rest now");
}

void PomodoroModel::SetupModel()
{
    if(!dataManager) return;
    taskModel = dataManager->GetDataModel(tableName);
    dataManager->SetActiveExtention(tableName, coreRelationName);
}

void PomodoroModel::OnTimerEnded(int timerId)
{
//    if(notificationTimerId != timerId) return;
    if(!currentTask.isValid()) return;
    auto branchIndex = currentTask;
    while(branchIndex.isValid())
    {
        auto pomodoros = branchIndex.data().toInt() + 1;
        taskModel->setData(branchIndex, QVariant(pomodoros));
        branchIndex = branchIndex.parent();
    }
    emit OnPomodoroFinished();
}
