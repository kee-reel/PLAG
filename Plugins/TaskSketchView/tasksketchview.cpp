#include "tasksketchview.h"

TaskSketchView::TaskSketchView()
{
    mainForm = new MainForm;
    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    myModel = NULL;
}

TaskSketchView::~TaskSketchView()
{
    delete paintWidgetTypeEditor;
    delete mainForm;
}

void TaskSketchView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void TaskSketchView::OnAllSetup()
{
    paintWidgetTypeEditor = new PaintWidget();
    myModel->LinkEditorWidget(new PaintWidget());
}

QString TaskSketchView::GetLastError()
{
    return "";
}

void TaskSketchView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
    case ROOTMODEL:
        break;
    case PLUGINMODEL:
        myModel = qobject_cast<ITaskSketchModel*>(pluginInfo->Instance);
        if(!myModel)
        {
            qDebug() << pluginInfo->Meta->Name << "is not ITaskListModel.";
            return;
        }
        qDebug() << "ITaskListModel succesfully set.";
        //connect(mainForm, SIGNAL(OnItemConvert(int)), pluginInfo->Instance, SIGNAL(OpenTaskEdit(int)));
        pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
        break;
    case PLUGINVIEW:
        break;
    case DATASOURCE:
        break;
    case DATAMANAGER:
        break;
    }
}

void TaskSketchView::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool TaskSketchView::Open(IModelPlugin *model)
{
    if(!myModel)
    {
        qDebug() << "Model isn't set!";
        return false;
    }
    mainForm->SetModel(myModel);
    emit OnOpen(mainForm);
    return true;
}

bool TaskSketchView::Close()
{
    emit OnClose(pluginInfo);
    emit OnClose();
    return true;
}
