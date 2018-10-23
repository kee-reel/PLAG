#include "tasksketchview.h"

TaskSketchView::TaskSketchView()
{
    paintWidgetTypeEditor = nullptr;
    mainForm = nullptr;
    myModel = nullptr;
}

TaskSketchView::~TaskSketchView()
{
    if(mainForm)
        delete mainForm;

    if(paintWidgetTypeEditor)
        delete paintWidgetTypeEditor;
}

void TaskSketchView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void TaskSketchView::OnAllSetup()
{
    mainForm = new MainForm();
    connect(mainForm, SIGNAL(onClose()), this, SLOT(Close()));
    paintWidgetTypeEditor = new PaintWidget();

    if(myModel)
        myModel->LinkEditorWidget(paintWidgetTypeEditor);
}

QString TaskSketchView::GetLastError()
{
    return "";
}

void TaskSketchView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
        case COREPLUGIN:
            break;

        case MODELPLUGIN:
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

        case VIEWPLUGIN:
            break;

        case DATASOURCEPLUGIN:
            break;

        case DATAMANAGERPLUGIN:
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
