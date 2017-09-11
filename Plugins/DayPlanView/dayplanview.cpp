#include "dayplanview.h"
#include "ui_form.h"

DayPlanView::DayPlanView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    openedView = NULL;
    openedModel = NULL;
    dayPlanModel = NULL;
    itemModel = NULL;
    ui->setupUi(this);
}

DayPlanView::~DayPlanView()
{
}

void DayPlanView::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void DayPlanView::OnAllSetup()
{
    if(itemModel == NULL) return;
    itemModel = dayPlanModel->GetModel();
    ui->treeView->setModel(itemModel);
}

QString DayPlanView::GetLastError()
{

}

void DayPlanView::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
    case PLUGINVIEW:{
        relatedViewPlugins.append(pluginInfo);
        qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
    } break;

    case PLUGINMODEL:{
        relatedModelPlugins.append(pluginInfo);
        qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));

        if(dayPlanModel = qobject_cast<IDayPlanModel*>(pluginInfo->Instance))
        {
            qDebug() << "IDayPlanModel Binded";
            pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
        }
    } break;

    case ROOTMODEL:{

    } break;

    case DATAMANAGER:{

    }break;
    }
}

void DayPlanView::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool DayPlanView::Open(IModelPlugin *model)
{
    qDebug() << "DayPlanView open.";

    // If something not set.
    if(false){
        qDebug() << "!DayPlanView not fully initialized!";
        return false;
    }

    emit OnOpen(this);
    return true;
}

bool DayPlanView::Close()
{
    qDebug() << "DayPlanView close.";
    // If view cannot close.
    if(false){
        qDebug() << "!DayPlanView cannot close right now!";
        return false;
    }
    openedView = NULL;
    openedModel = NULL;
    emit OnClose(pluginInfo);
    emit OnClose();
    return true;
}
