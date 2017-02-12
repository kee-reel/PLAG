#include "tasklistview.h"

TaskListView::TaskListView()
{
    model = NULL;
}

TaskListView::~TaskListView()
{
}

void TaskListView::SetModel(QObject* model)
{
    this->model = qobject_cast<ITaskListModel*>(model);
    if(!this->model)
    {
        qDebug() << model->objectName() << "is not ITaskListModel.";
    }
    qDebug() << "IMainMenuPluginModel succesfully set.";
}

bool TaskListView::Open(QWidget* parent)
{
    if(!model)
    {
        qDebug() << "Model isnt set!";
        return false;
    }
    qDebug() << "Open empty plugin.";
    return false;
}

bool TaskListView::Close()
{
    if(!model)
    {
        qDebug() << "Model isnt set!";
        return false;
    }
    qDebug() << "Close empty plugin.";
    return true;
}
