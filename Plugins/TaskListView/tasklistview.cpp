#include "tasklistview.h"

TaskListView::TaskListView()
{
    mainForm = new MainForm;
}

TaskListView::~TaskListView()
{
    delete mainForm;
}

void TaskListView::SetModel(QObject* model)
{
    myModel = qobject_cast<ITaskTreeModel*>(model);
    if(myModel)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
    }
    qDebug() << "ITaskListModel succesfully set.";
}

bool TaskListView::Open(int id, QWidget* parent)
{
    qDebug() << "View OPEN";
    taskTree = myModel->GetTaskTree();
    mainForm->SetModel(taskTree);
    myId = id;
    mainForm->setParent(parent);
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
