#include "tasklistview.h"

TaskListView::TaskListView()
{
    mainForm = new MainForm;
    myModel = NULL;
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
    qDebug() << "A";
    taskTree = myModel->GetTreeModel();
    qDebug() << "A";
    mainForm->SetModel(taskTree);
    qDebug() << "A";
    myId = id;
    mainForm->setParent(parent);
    qDebug() << "A";
    mainForm->resize(parent->size());
    mainForm->setVisible(true);
    connect(mainForm, SIGNAL(onClose()), this, SLOT(onClose()));
    return true;
}

bool TaskListView::Close()
{
    mainForm->setVisible(false);
    disconnect(mainForm, SIGNAL(onClose()), this, SLOT(onClose()));
    return true;
}

void TaskListView::onClose()
{
    myModel->Close();
}
