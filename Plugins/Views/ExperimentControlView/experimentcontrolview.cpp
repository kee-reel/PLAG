#include "experimentcontrolview.h"
#include "ui_form.h"

ExperimentControlView::ExperimentControlView(QWidget *parent) :
    QWidget(parent),
      ui(new Ui::Form)
{
    myReferencedPlugin = NULL;
    ui->setupUi(this);

    connect(ui->buttonExit, SIGNAL(clicked(bool)), this, SLOT(Close()));
}

ExperimentControlView::~ExperimentControlView()
{
}

void ExperimentControlView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void ExperimentControlView::OnAllSetup()
{

}

QString ExperimentControlView::GetLastError()
{

}

void ExperimentControlView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    /* Select your reference plugin case and get it. For example:
        case PLUGINMODEL:{
            myReferencedPlugin = qobject_cast<ISomePlugin*>(pluginInfo->Instance);
            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ISomePlugin.";
                return;
            }
            qDebug() << "ISomePlugin succesfully set.";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;
    */

    switch(pluginInfo->Meta->Type){
    case PLUGINVIEW:{
    } break;

    case PLUGINMODEL:{
        myReferencedPlugin = qobject_cast<IExperimentControlModel*>(pluginInfo->Instance);
        if(!myReferencedPlugin)
        {
            qDebug() << pluginInfo->Meta->Name << "is not ISomePlugin.";
            return;
        }
        qDebug() << "ISomePlugin succesfully set.";
        myReferencedPlugin->AddReferencePlugin(this->pluginInfo);
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
    } break;

    case ROOTMODEL:{
    } break;

    case DATAMANAGER:{
    }break;
    }
}

void ExperimentControlView::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool ExperimentControlView::Open(IModelPlugin *model)
{
    qDebug() << "ExperimentControlView open.";

    // If something not set.
    if(false){
        qDebug() << "!ExperimentControlView not fully initialized!";
        return false;
    }

    emit OnOpen(this);
    return true;
}

bool ExperimentControlView::Close()
{
    qDebug() << "ExperimentControlView close.";
    // If view cannot close.
    if(false){
        qDebug() << "!ExperimentControlView cannot close right now!";
        return false;
    }
    emit OnClose(pluginInfo);
    emit OnClose();
    return true;
}
