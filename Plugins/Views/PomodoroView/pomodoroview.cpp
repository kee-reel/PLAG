#include "pomodoroview.h"
#include "ui_pomodoroview.h"

PomodoroView::PomodoroView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PomodoroView)
{
    myModel = nullptr;

    ui->setupUi(this);
    ui->treeView->setVisible(false);
    ui->buttonEdit->setVisible(false);
    ui->buttonDelete->setVisible(false);
    ui->buttonAdd->setVisible(false);

    connect(ui->buttonExit, SIGNAL(clicked(bool)), SLOT(Close()));

#ifdef Q_OS_ANDROID
    ui->buttonAdd->setFocusPolicy(Qt::NoFocus);
    ui->buttonAdd->setToolTip("");
    ui->buttonDelete->setFocusPolicy(Qt::NoFocus);
    ui->buttonDelete->setToolTip("");
    ui->buttonEdit->setFocusPolicy(Qt::NoFocus);
    ui->buttonEdit->setToolTip("");
    ui->buttonProjects->setFocusPolicy(Qt::NoFocus);
    ui->buttonProjects->setToolTip("");
    ui->buttonExit->setVisible(false);
#endif
}

PomodoroView::~PomodoroView()
{
    delete ui;
}

void PomodoroView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void PomodoroView::OnAllSetup()
{
}

QString PomodoroView::GetLastError()
{

}

void PomodoroView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    if(pluginInfo->Meta->Type == MODELPLUGIN)
    {
        myModel = qobject_cast<IPomodoroModel*>(pluginInfo->Instance);
        if(!myModel)
        {
            qDebug() << pluginInfo->Meta->Name << "is not ITaskListModel.";
            return;
        }
        qDebug() << "ITaskListModel succesfully set.";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        connect(ui->pomodoroButton, SIGNAL(OnStartPomodoro()), pluginInfo->Instance, SLOT(StartPomodoro()));
        connect(pluginInfo->Instance, SIGNAL(OnPomodoroFinished()), SLOT(PomodoroFinished()));
        pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
    }
}

void PomodoroView::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

void PomodoroView::InstallWorkSetup()
{
    workSetup = myModel->GetWorkSetup();
    ui->pomodoroButton->secsTarget = workSetup.workSessionDuration;
    UpdateSelectedTask();
}

bool PomodoroView::Open(IModelPlugin *model)
{
    if(!myModel){
        qDebug() << "Model isn't set!";
        return false;
    }
    proxyModel = myModel->GetTaskModel();
    ui->treeView->setModel(proxyModel);
    InstallWorkSetup();
    emit OnOpen(this);
    return true;
}

bool PomodoroView::Close()
{
    emit OnClose(pluginInfo);
    emit OnClose();
    return true;
}

void PomodoroView::PomodoroFinished()
{
    UpdateSelectedTask();
//    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(finishedPomodoros->data().toString()));
}

void PomodoroView::on_buttonProjects_clicked()
{
    bool isTimerButtonVisible = !ui->pomodoroButton->isVisible();
    ui->buttonProjects->setIcon(QIcon(
        isTimerButtonVisible ?
        ":/Res/ic_assignment_black_36dp.png" :
        ":/Res/ic_timelapse_black_24dp.png"));
    ui->treeView->      setVisible(!isTimerButtonVisible);
    ui->pomodoroButton->setVisible(isTimerButtonVisible);
    ui->buttonEdit->    setVisible(!isTimerButtonVisible);
    ui->buttonDelete->  setVisible(!isTimerButtonVisible);
    ui->buttonAdd->     setVisible(!isTimerButtonVisible);
}

void PomodoroView::on_buttonEdit_clicked()
{
    auto list = ui->treeView->selectionModel()->selectedRows();
    if(list.length() == 0) return;
}

void PomodoroView::on_buttonDelete_clicked()
{
    auto list = ui->treeView->selectionModel()->selectedIndexes();
    for(int i = list.count()-1; i >= 0; --i)
        proxyModel->removeRows(list[i].row(), 1, list[i].parent());
}

void PomodoroView::on_buttonAdd_clicked()
{
    proxyModel->insertRow(0);
}

void PomodoroView::UpdateSelectedTask()
{
    bool isTaskValid = currentTask.isValid();
    auto taskName = isTaskValid ? currentTask.data().toString() : "Task not selected";
    ui->labelProject->setText(taskName);
    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(taskName));
    ui->pomodoroButton->isEnabled = isTaskValid;
}

void PomodoroView::on_treeView_pressed(const QModelIndex &index)
{
    auto list = ui->treeView->selectionModel()->selectedIndexes();
    if(list.length() == 0) return;
    auto selected = list.first();

    currentTask = selected;
    myModel->SetActiveProject(currentTask);

    UpdateSelectedTask();
}

bool PomodoroView::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->pomodoroButton && event->type() == QEvent::MouseButtonRelease)
    {
        return currentTask.isValid();
    }
    return QWidget::eventFilter(watched, event);
}

void PomodoroView::on_treeView_clicked(const QModelIndex &index)
{

}
