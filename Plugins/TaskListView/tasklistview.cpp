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

void TaskListView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void TaskListView::OnAllSetup()
{

}

QString TaskListView::GetLastError()
{
    return "";
}

void TaskListView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
        case PLUGINMODEL:{
            myModel = qobject_cast<ITaskTreeModel*>(pluginInfo->Instance);
            if(!myModel)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ITaskListModel.";
                return;
            }
            qDebug() << "ITaskListModel succesfully set.";
            connect(pluginInfo->Instance, SIGNAL(OpenTaskEdit(int)), SLOT(OpenTaskEditor(int)));
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
            pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
        }
    }
}

void TaskListView::ReferencePluginClosed(PluginInfo *pluginInfo)
{

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
    emit OnClose();
    emit OnClose(pluginInfo);
    //myModel->CloseFromView(this);
    return true;
}

void TaskListView::OpenTaskEditor(int id)
{
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!" << id;
    //Open(NULL, );
}
