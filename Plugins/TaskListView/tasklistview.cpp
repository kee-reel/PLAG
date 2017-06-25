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
    return "";
}

void TaskListView::AddModel(QObject* model)
{
    myModel = qobject_cast<ITaskTreeModel*>(model);
    if(!myModel)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
        return;
    }
    qDebug() << "ITaskListModel succesfully set.";
    connect(model, SIGNAL(OpenTaskEdit(int)), SLOT(OpenTaskEditor(int)));
}

bool TaskListView::Open(IModelPlugin *model, QWidget* parent)
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

    if(parent) parent->layout()->addWidget(mainForm);
    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    mainForm->setParent(parent);
    mainForm->show();
    return true;
}

bool TaskListView::Close()
{
    qDebug() << "CLOSE";
    disconnect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    mainForm->hide();
    myModel->CloseFromView(this);
    return true;
}

void TaskListView::OpenTaskEditor(int id)
{
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!" << id;
    Open(NULL);
}
