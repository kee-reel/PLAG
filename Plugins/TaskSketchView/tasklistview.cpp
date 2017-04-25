#include "tasklistview.h"

TaskListView::TaskListView()
{
    mainForm = new MainForm;
    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
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
    myModel = qobject_cast<ITaskSketchModel*>(model);
    if(!myModel)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
        return;
    }
    qDebug() << "ITaskListModel succesfully set.";
    connect(mainForm, SIGNAL(OnItemConvert(int)), model, SIGNAL(OpenTaskEdit(int)));
}

bool TaskListView::Open(QWidget* parent)
{
    qDebug() << "View OPEN" << parent;
    if(!myModel)
    {
        qDebug() << "Model isn't set!";
        return false;
    }
    parent->layout()->addWidget(mainForm);
    mainForm->setParent(parent);
    mainForm->show();
    mainForm->SetModel(myModel);
    return true;
}

bool TaskListView::Close()
{
    qDebug() << "CLOSE";
    mainForm->hide();
    myModel->CloseFromView(this);
    return true;
}
