#include "timermodel.h"


TimerModel::TimerModel()
{
    // myReferencedPlugin = nullptr;
    openedView = nullptr;
    openedModel = nullptr;
    /*
    ui->setupUi(this);
    */
}

TimerModel::~TimerModel()
{
}

void TimerModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void TimerModel::OnAllSetup()
{

}

QString TimerModel::GetLastError()
{

}

void TimerModel::AddReferencePlugin(PluginInfo *pluginInfo)
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
    case VIEWPLUGIN:{
        relatedViewPlugins.append(pluginInfo);
        qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
    } break;

    case MODELPLUGIN:{
        relatedModelPlugins.append(pluginInfo);
        qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
    } break;

    case COREPLUGIN:{
    } break;

    case DATAMANAGERPLUGIN:{
    }break;
    }
}

void TimerModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool TimerModel::Open(IModelPlugin *parent)
{
    qDebug() << "TimerModel open.";
    if(relatedViewPlugins.count() == 0){
        qDebug() << "!TimerModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "TimerModel opens related view " << openedView->Meta->Name;
    if(!openedView->Plugin.view->Open(this)){
        qDebug() << "!Can't open first view!";
        openedView = nullptr;
        return false;
    }
    return true;
}

void TimerModel::Close()
{
    qDebug() << "TimerModel close.";
    if(openedView != nullptr && !openedView->Plugin.view->Close()){
        qDebug() << "View plugin" << openedView->Meta->Name
                 << "not closed, but model closing anyway.";
    }
    if(openedModel != nullptr)
        openedView->Plugin.view->Close();

    openedView = nullptr;
    openedModel = nullptr;
    emit OnClose(pluginInfo);
    emit OnClose();
}

