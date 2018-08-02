#include "tasklistview.h"

TaskListView::TaskListView()
{
    mainForm = new MainForm;
    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    myModel = nullptr;
    taskTree = nullptr;
    proxyModel = nullptr;
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
    QFile f(":Res/qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
}

QString TaskListView::GetLastError()
{
    return "";
}

void TaskListView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
        case MODELPLUGIN:{
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

bool TaskListView::Open(IModelPlugin *model)
{
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
    emit OnOpen(mainForm);

    return true;
}

bool TaskListView::Close()
{
    qDebug() << "CLOSE";
    emit OnClose();
    emit OnClose(pluginInfo);
    return true;
}

void TaskListView::OpenTaskEditor(int id)
{
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!" << id;
}
