#include "pomodoromanager.h"

PomodoroManager::PomodoroManager() :
    PluginBase()
{
    myModel = nullptr;
    taskModel = nullptr;
    notificationManager = nullptr;
    dataManager = nullptr;
    tableName = "IUserTaskManager";
    coreRelationName = "iPomodoroManager";
    workSetup.easyRestDuration = 5 * 60;
    workSetup.longRestDuration = 15 * 60;
    workSetup.longRestPeriod = 3;
    workSetup.workSessionDuration = 35 * 60;
}

PomodoroManager::~PomodoroManager()
{
}

void PomodoroManager::onAllReferencesSet()
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
        else if(!QString::compare(interfaceName, "INotificationManager", Qt::CaseInsensitive))
        {
            notificationManager = castPluginToInterface<INotificationManager>(plugin);
            auto instance = plugin->getObject();
            auto res = connect(instance, SIGNAL(OnTimerTimeout(int)), SLOT(OnTimerEnded(int)));
        }
    }
    PluginBase::onAllReferencesSet();
}

void PomodoroManager::onAllReferencesReady()
{
    QMap<QString, QVariant::Type> newRelationStruct = {
        {"pomodoros",   QVariant::Int}
    };
    QVector<QVariant> defaultData;
    defaultData << 0;
    dataManager->AddExtention(tableName, coreRelationName, newRelationStruct, defaultData);

    taskModel = dataManager->GetDataModel(tableName);
    dataManager->SetActiveExtention(tableName, coreRelationName);

    PluginBase::onAllReferencesReady();
}

QAbstractItemModel *PomodoroManager::GetTaskModel()
{
    return taskModel;
}

void PomodoroManager::SetActiveProject(QModelIndex index)
{
    currentTask = index;
}

QModelIndex* PomodoroManager::GetActiveProject()
{
    return &currentTask;
}

IPomodoroManager::WorkSetup PomodoroManager::GetWorkSetup()
{
    return workSetup;
}

void PomodoroManager::StartPomodoro()
{
    notificationTimerId = notificationManager->
            SetAlarm(INotificationManager::RTC_TIME,
                     QDateTime::currentDateTime().addSecs(workSetup.workSessionDuration));

    notificationManager->SetAlarmedNotification(INotificationManager::RTC_TIME,
             QDateTime::currentDateTime().addSecs(workSetup.workSessionDuration),
                           "Message from Pomodoro:",
                           "You can take a rest now");
}

void PomodoroManager::OnTimerEnded(int timerId)
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
