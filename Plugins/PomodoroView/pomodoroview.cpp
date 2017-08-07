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
    connect(button, SIGNAL(PomodoroFinished()), SLOT(OnPomodoroFinished()));
<<<<<<< HEAD
    ui->verticalLayout->insertWidget(2, button);
    finishedPomodoros = 0;
=======
    ui->horizontalLayout->insertWidget(1, button);
>>>>>>> a2445897c806490964d364d39f2b23b415a47371
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

bool PomodoroView::Open(IModelPlugin *model, QWidget *parent)
{
    qDebug() << "View OPEN" << parent;
    if(!myModel)
    {
        qDebug() << "Model isn't set!";
        return false;
    }
    parent->layout()->addWidget(this);
    setParent(parent);
    ui->treeView->setModel(myModel->GetInternalModel());
    show();
    return true;
}

bool PomodoroView::Close()
{
    qDebug() << "CLOSE";
    hide();
    emit OnClose(pluginInfo);
    emit OnClose();
    return true;
}

void PomodoroView::OnPomodoroFinished()
{
    ++finishedPomodoros;
    ui->pomodoroCountLabel->setText(QString("%1 pomodoros").arg(finishedPomodoros));
}
