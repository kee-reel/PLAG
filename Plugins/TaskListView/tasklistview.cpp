#include "tasklistview.h"

TaskListView::TaskListView()
{
    mainForm = new MainForm;

    myModel = NULL;
    taskTree = NULL;
    proxyModel = NULL;
}

TaskListView::~TaskListView()
{
    delete mainForm;
}

void TaskListView::OnAllSetup()
{

}

QString TaskListView::GetLastError()
{

}

void TaskListView::SetModel(QObject* model)
{
    myModel = qobject_cast<ITreeModel*>(model);
    if(!myModel)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
        return;
    }
    qDebug() << "ITaskListModel succesfully set.";
}

bool TaskListView::Open(int id, QWidget* parent)
{
    qDebug() << "View OPEN" << parent;
    if(!myModel)
    {
        qDebug() << "Model isn't set!";
        return false;
    }

    if(!taskTree)
    {
        taskTree = myModel->GetTreeModel();
        proxyModel = new DesignProxyModel(taskTree);
        mainForm->SetModel(proxyModel);
    }

    parent->layout()->addWidget(mainForm);
    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    myId = id;
    mainForm->setParent(parent);
    mainForm->show();
    return true;
}

bool TaskListView::Close()
{
    qDebug() << "CLOSE";
    disconnect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    mainForm->hide();
    myModel->Close();
    return true;
}
