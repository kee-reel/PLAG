#include "pomodoromanagerview.h"
#include "ui_form.h"

PomodoroManagerView::PomodoroManagerView(QWidget *parent) :
    PluginBase(parent)
{
    myModel = nullptr;

    ui->treeView->setVisible(false);
    ui->buttonEdit->setVisible(false);
    ui->buttonDelete->setVisible(false);
    ui->buttonAdd->setVisible(false);

    connect(ui->buttonAdd, SIGNAL(clicked(bool)), this, SLOT(on_buttonAdd_clicked()));
    connect(ui->buttonEdit, SIGNAL(clicked(bool)), this, SLOT(on_buttonEdit_clicked()));
    connect(ui->buttonDelete, SIGNAL(clicked(bool)), this, SLOT(on_buttonDelete_clicked()));
    connect(ui->buttonProjects, SIGNAL(clicked(bool)), this, SLOT(on_buttonProjects_clicked()));
    connect(ui->treeView, SIGNAL(pressed(const QModelIndex &)), this, SLOT(on_treeView_pressed(const QModelIndex &)));
    connect(ui->buttonExit, SIGNAL(clicked(bool)), SLOT(on_buttonExit_clicked()));

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

PomodoroManagerView::~PomodoroManagerView()
{
}

void PomodoroManagerView::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IPomodoroManager", Qt::CaseInsensitive))
        {
            myModel = castPluginToInterface<IPomodoroManager>(plugin);
            auto instance = plugin->getObject();
            connect(ui->pomodoroButton, SIGNAL(OnStartPomodoro()), instance, SLOT(StartPomodoro()));
            connect(instance, SIGNAL(OnPomodoroFinished()), SLOT(PomodoroFinished()));
        }
    }
    PluginBase::onAllReferencesSet();
}

void PomodoroManagerView::onAllReferencesReady()
{
    proxyModel = myModel->GetTaskModel();
    ui->treeView->setModel(proxyModel);
    workSetup = myModel->GetWorkSetup();
    ui->pomodoroButton->secsTarget = workSetup.workSessionDuration;
    UpdateSelectedTask();

    PluginBase::onAllReferencesReady();
}

void PomodoroManagerView::PomodoroFinished()
{
    UpdateSelectedTask();
//    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(finishedPomodoros->data().toString()));
}

void PomodoroManagerView::on_buttonProjects_clicked()
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

void PomodoroManagerView::on_buttonEdit_clicked()
{
    auto list = ui->treeView->selectionModel()->selectedRows();
    if(list.length() == 0) return;
}

void PomodoroManagerView::on_buttonDelete_clicked()
{
    auto list = ui->treeView->selectionModel()->selectedIndexes();
    for(int i = list.count()-1; i >= 0; --i)
        proxyModel->removeRows(list[i].row(), 1, list[i].parent());
}

void PomodoroManagerView::on_buttonAdd_clicked()
{
    proxyModel->insertRow(0);
}

void PomodoroManagerView::on_buttonExit_clicked()
{
    emit onClose(this);
}

void PomodoroManagerView::UpdateSelectedTask()
{
    bool isTaskValid = currentTask.isValid();
    auto taskName = isTaskValid ? currentTask.data().toString() : "Task not selected";
    ui->labelProject->setText(taskName);
    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(taskName));
    ui->pomodoroButton->isEnabled = isTaskValid;
}

void PomodoroManagerView::on_treeView_pressed(const QModelIndex &index)
{
    auto list = ui->treeView->selectionModel()->selectedIndexes();
    if(list.length() == 0) return;
    auto selected = list.first();

    currentTask = selected;
    myModel->SetActiveProject(currentTask);

    UpdateSelectedTask();
}

bool PomodoroManagerView::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->pomodoroButton && event->type() == QEvent::MouseButtonRelease)
    {
        return currentTask.isValid();
    }
    return QWidget::eventFilter(watched, event);
}
