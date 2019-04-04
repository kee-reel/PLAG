#include "pomodoromodel.h"

PomodoroModel::PomodoroModel() :
    PluginBase()
{
    myModel = nullptr;
    taskModel = nullptr;
    notificationManager = nullptr;
    dataManager = nullptr;
    tableName = "itasktreemodel";
    coreRelationName = "ipomodoromodel";
    workSetup.easyRestDuration = 5 * 60;
    workSetup.longRestDuration = 15 * 60;
    workSetup.longRestPeriod = 3;
    workSetup.workSessionDuration = 35 * 60;
}

PomodoroModel::~PomodoroModel()
{
}

void PomodoroModel::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IExtendableDataManager", Qt::CaseInsensitive))
        {
            dataManager = castPluginToInterface<IExtendableDataManager>(plugin);
        }
        else if(!QString::compare(interfaceName, "ITaskTreeModel", Qt::CaseInsensitive))
        {
            myModel = castPluginToInterface<ITaskTreeModel>(plugin);
        }
        else if(!QString::compare(interfaceName, "INotificationManagerModel", Qt::CaseInsensitive))
        {
            notificationManager = castPluginToInterface<INotificationManagerModel>(plugin);
            auto instance = plugin->getObject();
            auto res = connect(instance, SIGNAL(OnTimerTimeout(int)), SLOT(OnTimerEnded(int)));
        }
    }
    PluginBase::onAllReferencesSet();
}

void PomodoroModel::onAllReferencesReady()
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
    notificationTimerId = notificationManager->
            SetAlarm(INotificationManagerModel::RTC_TIME,
                     QDateTime::currentDateTime().addSecs(workSetup.workSessionDuration));

    notificationManager->SetAlarmedNotification(INotificationManagerModel::RTC_TIME,
             QDateTime::currentDateTime().addSecs(workSetup.workSessionDuration),
                           "Message from Pomodoro:",
                           "You can take a rest now");
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
