#include "pomodoroview.h"
#include "ui_pomodoroview.h"

PomodoroView::PomodoroView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PomodoroView)
{
    ui->setupUi(this);
    connect(ui->buttonExit, SIGNAL(clicked(bool)), SLOT(Close()));
    myModel = NULL;
    button = ui->pomodoroButton;
    ui->treeView->setVisible(false);
    connect(button, SIGNAL(PomodoroFinished()), SLOT(OnPomodoroFinished()));
    ui->verticalLayout->insertWidget(2, button);
    isTimerWindow = true;
    addForm = new AddForm(this);
    ui->buttonEdit->setVisible(false);
    ui->buttonDelete->setVisible(false);
    ui->buttonAdd->setVisible(false);

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
    if(pluginInfo->Meta->Type == PLUGINMODEL)
    {
        myModel = qobject_cast<IPomodoroModel*>(pluginInfo->Instance);
        if(!myModel)
        {
            qDebug() << pluginInfo->Meta->Name << "is not ITaskListModel.";
            return;
        }
        qDebug() << "ITaskListModel succesfully set.";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
    }
}

void PomodoroView::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool PomodoroView::Open(IModelPlugin *model)
{
    if(!myModel){
        qDebug() << "Model isn't set!";
        return false;
    }
    auto columns = QVector<int> {0};
    proxyModel = new DesignProxyModel(myModel->GetInternalModel(), columns);
    currentProject = myModel->GetActiveProject();
    finishedPomodoros = myModel->GetCompletedPomodoros();
    ui->treeView->setModel(proxyModel);
    addForm->SetModel(proxyModel);
    ui->labelProject->setText(currentProject->data().toString());
    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(finishedPomodoros->data().toString()));
    emit OnOpen(this);
    return true;
}

bool PomodoroView::Close()
{
    emit OnClose(pluginInfo);
    emit OnClose();
    return true;
}

void PomodoroView::OnPomodoroFinished()
{
    myModel->IncrementPomodoro();
    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(finishedPomodoros->data().toString()));
}

void PomodoroView::on_buttonProjects_clicked()
{
    isTimerWindow = !isTimerWindow;

    ui->buttonProjects->setIcon(QIcon(
        isTimerWindow ?
        ":/Res/ic_assignment_black_36dp.png" :
        ":/Res/ic_timelapse_black_24dp.png"));
    ui->treeView->setVisible(!isTimerWindow);
    ui->pomodoroButton->setVisible(isTimerWindow);
    ui->buttonEdit->setVisible(!isTimerWindow);
    ui->buttonDelete->setVisible(!isTimerWindow);
    ui->buttonAdd->setVisible(!isTimerWindow);
}

void PomodoroView::on_buttonEdit_clicked()
{
    auto list = ui->treeView->selectionModel()->selectedRows();
    if(list.length() == 0) return;
    addForm->ShowModelData(list.first());
}

void PomodoroView::resizeEvent(QResizeEvent *event)
{
    addForm->resize(event->size());
}

void PomodoroView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Back) {
        Close();
    }
    event->accept();
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

void PomodoroView::on_treeView_pressed(const QModelIndex &index)
{
    auto list = ui->treeView->selectionModel()->selectedIndexes();
    if(list.length() == 0) return;
    auto selected = list.first();
    myModel->SetActiveProject(selected);
    ui->labelProject->setText(currentProject->data().toString());
    qDebug() << currentProject->data().toString();
    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(finishedPomodoros->data().toString()));
}

void PomodoroView::on_treeView_clicked(const QModelIndex &index)
{

}
